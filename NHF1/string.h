#ifndef STRING_H
#define STRING_H

#include <cstdio>
#include <cstring>

#include <iostream>

/** \file */

/** \brief
    * String értékeket és a hozzájuk tartozó referenciaszámlálókat tartalmazó
    * és kezelő segédobjektum.
    */
class StringValue
{
public:

    /** \brief
     * Az alapértelmezett konstruktora az osztálynak. A megadott stringértéket eltárolja,
     * a referenciaszámlálót pedig 1-re állítja. Explicit, tehát ilyet nem írhatunk le: StringValue a = "hello";
     */
    explicit StringValue( const char* str ) : m_refCount {1}
    {
        m_size = strlen( str ) + 1; // Az strlen()-ben nincs a lezáró 0!
        m_string = new char[m_size];
        strcpy( m_string, str ); // Bele fog férni, nem kell strncpy(), és ez így gyorsabb
    }

    StringValue( const char* lhs, const char* rhs ) : m_refCount {1}
    {
        m_size = strlen( lhs ) + strlen( rhs ) + 1; // +1 -> lezáró 0
        m_string = new char[m_size];
        snprintf( m_string, m_size, "%s%s", lhs, rhs );
    }

    operator const char*() const
    {
        return m_string;
    }

    /** \brief
     * Megnöveli a StringValue referenciaszámlálóját.
     * \return A megnövelt referenciaszámláló új értéke.
     */
    unsigned long int increase_refCount()
    {
        return ++m_refCount;
    }

    /** \brief
     * Csökkenti a StringValue referenciaszámlálóját, ha az nagyobb, mint 0.
     *
     * \throw   "const char* "
     *          Ha a refernciaszámláló már 0, akkor egy C stringet dob kivételként.\n
     *          Normális esetben ez nem kéne megtörténjen, fel kell szabadítania a
     *          0 referenciaszámlálójú objektumokat
     * \return A csökkentett referenciaszámláló új értéke. Ha ez 0, akkor törölni kell az objektumot!
     */
    unsigned long int decrease_refCount() throw( const char* )
    {
        if( m_refCount > 0 ) return --m_refCount;
        else throw "StringValue reference counter is 0 already";
    }

    ~StringValue()
    {
        delete[] m_string;
    }

    /** \brief
     * A referenciaszámláló aktuális értékét adja vissza. Általános esetben ezt nem kell használni!
     *
     * A referenciaszámláló értékét állítgató függvények visszatérési értékét használd helyette.
     * (StringValue::increase_refCount(), StringValue::decrease_refCount())
     * \return A referenciaszámláló értéke.
     */
    unsigned long int getRefCount()
    {
        return m_refCount;
    }

    size_t getSize() const
    {
        return m_size;
    }
private:
    unsigned long int m_refCount;
    char* m_string;
    size_t m_size;
};


/** \brief
 * Referenciaszámlálással rendelkező stringértékekkel működő, általános szöveg osztály.
 *
 * Létrehozható hagyományos C stringből, beolvasva is (pl std::cin-ről), kiírható a kimenetre, összefűzhető stringgel és karakterrel.
 * A használónak nem kell törődnie a belső erőforrások kezelésével, az megtörténik automatikusan.
 */
class String
{
public:

    /** \brief
     * Új Stringet hoz létre hagyományos C stringből.
     * \param str Az értékként adott C string. Ha nincs megadva, akkor üres stringre inicializálódik az objektum.
     */
    String( const char* str  = "" );


    /** \brief
     * Új Stringet hoz létre egy másik Stringből.
     * Nem másolja le a StringValue-ját a másiknak, csak elkéri a referenciát rá (ez megnöveli a referenciaszámlálót)
     * \param other Inicializált, nem jobbérték String.
     */
    String( String const& other );


    String( String && rval );

    String & operator=( String const & other );

    String & operator=( String && rval );
    String & operator=( const char* str );


    /** \brief
     * Törli a Stringet. A mutatott StringValue nem törlődik, csak csökken eggyel a referenciaszámlálója.
     * (Persze ilyenkor törlődhet, ha a referenciaszámláló 0 lesz...)
     */
    ~String();

    size_t length() const
    {
        return m_stringValue->getSize();
    }

    operator const char*() const
    {
        return ( const char* )( *m_stringValue );
    }

    StringValue* getStringValue()
    {
        return m_stringValue;
    }

#ifdef _DEBUG_
    static int _Num_Instances;
#endif

private:

    void abandon_stringValue( void )
    {
        if( m_stringValue != nullptr && m_stringValue->decrease_refCount() == 0 )
        {
            delete m_stringValue;
        }
    }

    StringValue* obtain_stringValue( void ) const
    {
        m_stringValue->increase_refCount();
        return m_stringValue;
    }

    StringValue* m_stringValue;
};

/** \brief
 * Összefűzi a paraméterként kapott két Stringet
 * \param lhs Az új string elejére kerülő rész.
 * \param rhs Az új string végé kerülő rész.
 * \return Az összefűzött String. Pl. lhs="hello ", rhs="world" -> "hello world"
 */
String operator+( String const& lhs, String const& rhs );

/** \brief
 * Hozzáfűz egy Stringhez megy másik Stringet.
 * \param lhs A String, amihez hozzá szeretnénk fűzni.
 * \param rhs A hozzáfűzendő String.
 * \return Az lhs paraméter, végére fűzve a jobb oldali részstring.
 */
String operator+=( String & lhs, String const& rhs );

std::ostream& operator<<( std::ostream& os, String const& str );

std::istream& operator>>(std::istream& is, String & str);

#endif /* STRING_H */

