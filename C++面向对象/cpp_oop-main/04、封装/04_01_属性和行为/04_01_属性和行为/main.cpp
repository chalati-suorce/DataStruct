#include <iostream>
using namespace std;
class Hero {
public:
    int   m_Id;  
    int   m_Hp;   

    void addHp(int hp) {
        m_Hp += hp;
    }

    void subHp(int hp) {
        m_Hp -= hp;
    }
};

int main() {
    
    Hero h;
   
    h.m_Id = 5;
    h.m_Hp = 100;
    h.addHp(100);
    cout << "Id 为" << h.m_Id << "的英雄，血量是" << h.m_Hp << endl;
    h.subHp(100);
    cout << "Id 为" << h.m_Id << "的英雄，血量是" << h.m_Hp << endl;

    return 0;
}