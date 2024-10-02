#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

//� ������������ ���� ������������ ������� ��������� ��������� ������������ ������ ������� ����� ����(���������� ��������,
//����������� ���������� �� ������ ���� �������).� ����� ���� ������� ���������, �������� �������, ���� �� �����.������� 
//�� ������� ��������� ��������� ��� ������� ������� ���������(��������).����� ���� ���������� � ���� ������� ��������� 
//������� ����, ��� ��������� �� ����� (����������� �������� ���������).�������� ��� �������, ���� � ������������ ������ �� 
//������� �� ���������, � �� ������� ���������� ����� ������������� ������, ����, �� ���� ������� ���� ���������, �� �������
//�� ������.���������� �������� ���������� �� ��������� ������� ����������(Builder).

class GiftSet;

// Abstract Builder class
class GiftSetBuilder {
protected:
    GiftSet* giftSet;

public:
    void CreateNewGiftSet();  
    GiftSet* GetMyGiftSet();

    virtual void SetLolipops() = 0;
    virtual void SetChocoladCandy() = 0;
    virtual void SetWaffles() = 0;
    virtual void SetDragee() = 0;
    virtual void SetPricePerKg() = 0;
};

// Candy class 
class Candy {
private:
    string type;
    double weight;
    double pricePerKg;

public:
    Candy(string type, double weight, double pricePerKg)
        : type(type), weight(weight), pricePerKg(pricePerKg) {}

    double getWeight() const { return weight; }
    double getPrice() const { return weight * pricePerKg / 1000; }
    string getType() const { return type; }
};


class GiftSet {
private:
    vector<Candy> candies;

public:
    void addCandy(const string& type, double weight, double pricePerKg) {
        candies.emplace_back(type, weight, pricePerKg);
    }

    void display() const {
        cout << "������������ ����:\n";
        double totalWeight = 0;
        double totalPrice = 0;

        for (const auto& candy : candies) {
            cout << "- " << candy.getType() << ": "
                << candy.getWeight() << " �, "
                << fixed << setprecision(2) << candy.getPrice() << " ���\n";
            totalWeight += candy.getWeight();
            totalPrice += candy.getPrice();
        }
        cout << "�������� ����: " << totalWeight << " �\n";
        cout << "�������� �������: " << fixed << setprecision(2) << totalPrice << " ���\n";
    }
};

// Define the missing methods in GiftSetBuilder
void GiftSetBuilder::CreateNewGiftSet() {
    giftSet = new GiftSet();
}

GiftSet* GiftSetBuilder::GetMyGiftSet() {
    return giftSet;
}

// ���������� ��������
class EconomyGiftSetBuilder : public GiftSetBuilder {
public:
    void SetLolipops() override {
        giftSet->addCandy("���������", 200, 150);
    }

    void SetChocoladCandy() override {
        giftSet->addCandy("�������� �������", 300, 150);
    }

    void SetWaffles() override {
        giftSet->addCandy("����", 250, 150);
    }

    void SetDragee() override {
        giftSet->addCandy("�����", 250, 150);
    }

    void SetPricePerKg() override {

    }
};

// ����������� ����������
class StandardGiftSetBuilder : public GiftSetBuilder {
public:
    void SetLolipops() override {
        giftSet->addCandy("���������", 300, 200);
    }

    void SetChocoladCandy() override {
        giftSet->addCandy("�������� �������", 400, 200);
    }

    void SetWaffles() override {
        giftSet->addCandy("����", 350, 200);
    }

    void SetDragee() override {
        giftSet->addCandy("�����", 350, 200);
    }

    void SetPricePerKg() override {

    }
};

// ������ ���� �������
class PremiumGiftSetBuilder : public GiftSetBuilder {
public:
    void SetLolipops() override {
        giftSet->addCandy("���������", 400, 300);
    }

    void SetChocoladCandy() override {
        giftSet->addCandy("�������� �������", 500, 300);
    }

    void SetWaffles() override {
        giftSet->addCandy("����", 450, 300);
    }

    void SetDragee() override {
        giftSet->addCandy("�����", 450, 300);
    }

    void SetPricePerKg() override {

    }
};

// Director class to construct GiftSet
class GiftSetDirector {
private:
    GiftSetBuilder* builder;

public:
    void setBuilder(GiftSetBuilder* b) {
        builder = b;
    }

    void constructGiftSet() {
        builder->CreateNewGiftSet();
        builder->SetLolipops();
        builder->SetChocoladCandy();
        builder->SetWaffles();
        builder->SetDragee();
    }
};


int main() {
    setlocale(LC_ALL, "Ukr");

    GiftSetDirector director;
    GiftSetBuilder* builder;

    string choice;
    cout << "������� ��� ������������� ������ (����������(1), �����������(2), ������(3): ";
    cin >> choice;

    if (choice == "1") {
        builder = new EconomyGiftSetBuilder();
    }
    else if (choice == "2") {
        builder = new StandardGiftSetBuilder();
    }
    else if (choice == "3") {
        builder = new PremiumGiftSetBuilder();
    }
    else {
        cout << "������� ����!\n";
        return 1;
    }

    director.setBuilder(builder);
    director.constructGiftSet();

    GiftSet* giftSet = builder->GetMyGiftSet();
    giftSet->display();

    delete giftSet;
    delete builder;

    return 0;
}
