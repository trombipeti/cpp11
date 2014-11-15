void foo() {} /* 1 */

void foo(int i) {} /* 2 */

class Foo {
    public:
        void foo(); /* 3 */
};
void Foo::foo() {}

namespace FooNS {
    void foo() {} /* 4 */

    class Foo {
        public:
            void foo(); /* 5 */
    };
    void Foo::foo() {}
}

int main(int argc, char *argv[]) {
    /* 1 */ foo();
    /* 2 */ foo(1);
    /* 3 */ Foo().foo(); 
    /* 4 */ FooNS::foo(); 
    /* 5 */ FooNS::Foo().foo(); 
}
