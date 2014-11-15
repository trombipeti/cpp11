/**
 * Általános, egyszerű bináris keresőfa osztály.
 * Az egyes csomópontoktól balra náluk kisebb vagy velük egyenlő értékek,
 * tőlük jobbra náluk nagyobb értékek szerepelnek.
 * A template-ként kapott típusnak rendelkeznie kell összehasonlító operátorokkal!
 */
template <typename T>
class BTree
{
public:
    /**
     * Egy elemű fát hoz létre a megadott értékkel.
     * @param A gyökér értéke
     */
    explicit BTree( T val ) : m_value { val }, m_leftChild {nullptr}, m_rightChild {nullptr}, m_inited { true } {}

    /**
     * Alapértelmezett konstruktor, amely egy érték nélküli fát hoz létre.
     * Így lehet úgy létrehozni egy fát, hogy a benne lévő értékeket majd
     * csak később, insert() hívásokkal töltjük föl.
     */
    BTree() : m_leftChild {nullptr}, m_rightChild {nullptr}, m_inited { false } {}

    /**
     * Beszúrja a megadott értéket a bináris fába.
     * @param val A beszúrni kívánt érték.
     */
    void insert( T val )
    {
        if( ! m_inited )
        {
            m_value = val;
            m_leftChild = m_rightChild = nullptr; // In case this is not done yet
            m_inited = true;
        }
        else
        {
            if( val <= m_value )
            {
                if( m_leftChild != nullptr ) m_leftChild->insert( val );
                else m_leftChild = new BTree { val };
            }
            else
            {
                if( m_rightChild != nullptr ) m_rightChild->insert( val );
                else m_rightChild = new BTree { val };
            }
        }
    }

    ~BTree()
    {
        if( m_leftChild != nullptr )
        {
            delete m_leftChild;
        }
        if( m_rightChild != nullptr )
        {
            delete m_rightChild;
        }
    }
private:
//    bool isLeaf()
//    {
//        return m_leftChild == m_rightChild == nullptr;
//    }

    T          m_value;
    BTree<T>*  m_leftChild;
    BTree<T>*  m_rightChild;

    bool m_inited;
};
