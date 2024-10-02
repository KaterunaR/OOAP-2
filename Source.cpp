#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

//У фасувальному цеху кондитерської фабрики проводять пакування подарункових наборів цукерок трьох типів(економічний «Ласунка»,
//стандартний «Наминайко» та екстра «Пан Коцький»).У кожен набір входять льодяники, шоколадні цукерки, вафлі та драже.Вартість 
//за кілограм солодощів вказується при запуску системи пакування(програми).Кожен набір складається з різної кількість солодощів 
//кожного типу, але однаковий за вагою (допускається невелике відхилення).Оператор сам визначає, який з подарункових наборів він 
//запускає на пакування, а на дисплей виводиться назва подарункового набору, ціна, та вага кожного виду солодощів, які входять
//до набору.Поставлене завдання реалізувати за допомогою шаблону Будівельник(Builder).

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
        cout << "Подарунковий набір:\n";
        double totalWeight = 0;
        double totalPrice = 0;

        for (const auto& candy : candies) {
            cout << "- " << candy.getType() << ": "
                << candy.getWeight() << " г, "
                << fixed << setprecision(2) << candy.getPrice() << " грн\n";
            totalWeight += candy.getWeight();
            totalPrice += candy.getPrice();
        }
        cout << "Загальна вага: " << totalWeight << " г\n";
        cout << "Загальна вартість: " << fixed << setprecision(2) << totalPrice << " грн\n";
    }
};

// Define the missing methods in GiftSetBuilder
void GiftSetBuilder::CreateNewGiftSet() {
    giftSet = new GiftSet();
}

GiftSet* GiftSetBuilder::GetMyGiftSet() {
    return giftSet;
}

// економічний «Ласунка»
class EconomyGiftSetBuilder : public GiftSetBuilder {
public:
    void SetLolipops() override {
        giftSet->addCandy("Льодяники", 200, 150);
    }

    void SetChocoladCandy() override {
        giftSet->addCandy("Шоколадні цукерки", 300, 150);
    }

    void SetWaffles() override {
        giftSet->addCandy("Вафлі", 250, 150);
    }

    void SetDragee() override {
        giftSet->addCandy("Драже", 250, 150);
    }

    void SetPricePerKg() override {

    }
};

// стандартний «Наминайко»
class StandardGiftSetBuilder : public GiftSetBuilder {
public:
    void SetLolipops() override {
        giftSet->addCandy("Льодяники", 300, 200);
    }

    void SetChocoladCandy() override {
        giftSet->addCandy("Шоколадні цукерки", 400, 200);
    }

    void SetWaffles() override {
        giftSet->addCandy("Вафлі", 350, 200);
    }

    void SetDragee() override {
        giftSet->addCandy("Драже", 350, 200);
    }

    void SetPricePerKg() override {

    }
};

// екстра «Пан Коцький»
class PremiumGiftSetBuilder : public GiftSetBuilder {
public:
    void SetLolipops() override {
        giftSet->addCandy("Льодяники", 400, 300);
    }

    void SetChocoladCandy() override {
        giftSet->addCandy("Шоколадні цукерки", 500, 300);
    }

    void SetWaffles() override {
        giftSet->addCandy("Вафлі", 450, 300);
    }

    void SetDragee() override {
        giftSet->addCandy("Драже", 450, 300);
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
    cout << "Виберіть тип подарункового набору (економічний(1), стандартний(2), екстра(3): ";
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
        cout << "Невірний вибір!\n";
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
