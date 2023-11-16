#include<iostream>



class test{
    protected:
        int num{};
    public:
        test(int value):num{value}{}
        void print()
        {
            std::cout<<num<<" "<<std::endl;
        }
};

int main()
{
    test one{34};
    one.print();

}