// FunctionCard.h

#ifndef FUNCTIONCARD_H
#define FUNCTIONCARD_H

#include <string>

enum class FunctionCardType {
    A_BeFruitful,   // �h�� *3
    A_FullTheEarth, // ���a�� *2
    A_Multiply,     // �T���� *2
    A_Golden,       // �����Ͽ� *2
    B_FallingRock,  // ���� *2
    B_Slump,        // �ɸ� *2
    B_Plague,       // �̯f *1
    B_Lightning,    // ���p *2
    B_Storm,        // �P *1
    S_Dominion,     // �βv *2
    S_SheepDog      // ���Ϥ� *2
};

class FunctionCard {
public:
    // �c�y���
    FunctionCard(FunctionCardType type);

    // ø�s�d�P�Ϥ���ù��W����k
    //void draw() const;

    // ����d�P�ƶq����k
    int num() const;

    // ����d�P��������k
    FunctionCardType getType() const;

    // ����d�P�W�٪���k
    std::string getName() const;

    // ���L�d�P�H������k
    void printCardInfo() const;

    // ����d�P�ʧ@��������k
    virtual void executeAction() = 0;

protected:
    FunctionCardType type; // �d�P����
    std::string name;      // �d�P�W��
    int quantity;          // �d�P�ƶq
    ALLEGRO_BITMAP *func = NULL;

private:
    // �[���d�P�Ϥ�����k�]�����{���M��ϥΪ��ϧήw�^
    void loadCardImage();
};

#endif // FUNCTIONCARD_H

/*
#ifndef FUNCTIONCARD_H
#define FUNCTIONCARD_H

#include <string>

// �w�q�\��d�������T�|
enum class FunctionCardType {
    A_BeFruitful,   // �h��
    A_FullTheEarth, // ���a��
    A_Multiply,     // �T����
    A_Golden,       // �����Ͽ�
    B_FallingRock,  // ����
    B_Slump,        // �ɸ�
    B_Plague,       // �̯f
    B_Lightning,    // ���p
    B_Storm,        // �P
    S_Dominion,     // �βv
    S_SheepDog      // ���Ϥ�
};

// �\��d���O
class FunctionCard {
public:
    // �c�y���
    FunctionCard(FunctionCardType type, const std::string &name);

    // ����d�P����
    FunctionCardType getType() const;

    // ����d�P�W��
    std::string getName() const;
    //*init();

    void Draw() ;

    // �µ�����ơA�w�q�d�P������欰
    virtual void executeAction() = 0;

    // �L�X�d�P�H���]�Ҧp�G�d�P�W�٩M�����^
    void printCardInfo() const;

    //*�d���ƶq

private:
    FunctionCardType type; // �d�P����
    std::string name;      // �d�P�W��
};

#endif // FUNCTIONCARD_H
*/
