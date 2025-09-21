#include <iostream>
#include <vector>
#include <string>

using namespace std;

class IDcountable
{
    public:
    virtual double applyDiscountable(double percentage) = 0;
};

class Product
{
    protected:
    string name;
    double price;
    int id;
    public:
    Product (string n, double pr, int ID )
    {
        name = n;
        price = pr;
        id = ID;
    }
    //Setter
    void setName(string n) {name = n;}
    void setPrice(double pr) {price = pr;}
    void setID(int ID) {id=ID;}

    //Getter
    string getName() {return name;}
    double getPrice() {return price;}
    int getID() {return id;}

    Product operator+(double extraPrice)
    {
     Product temp = *this;
     temp.price += extraPrice;
     return temp;   
    }

   virtual void displayInfo()
    {
        cout << "Name of product: " << name << endl;
        cout << "ID of product: " << id << endl;
        cout << "Price of product: " << price << endl; 
    }

};

class Electronic : public Product, public IDcountable
{
    private:
    string brand;
    public:
    Electronic (string n, double pr, int ID, string br) : Product ( n, pr, ID)
    {
        brand = br;
    }

    //Setter
    void setBrand(string br) {brand=br;}
    //Getter
    string getBrand() {return brand;}

    double applyDiscountable(double percentage) override
    {
        price = price - (price * percentage/100);
        return price;
    }

    void displayInfo() override
    {
        cout << "Name of electronic product : " << name << endl;
        cout << "ID of electronic product : " << id << endl;
        cout << "Brand : " << brand << endl;
        cout << "Price : " << price << endl;
    }

};

class ShoppingCart
{
private:
    string nameCart;
    vector <Product*> bookedProduct;
public:
    ShoppingCart (string name)
    {
        nameCart = name;
    }
    //Setter
    void setItem(string name) {nameCart= name;}
    //Getter
    string getItem() {return nameCart;}

    void addItem(Product* p)
    {
        bookedProduct.push_back(p);
        cout << "Added " << p->getName() << " into the Shopping Cart !" << endl; 
    }

    void showCart()
    {
        for (int i=0;i<bookedProduct.size();i++)
        {
            bookedProduct[i] -> displayInfo();
            cout << endl;
        }
    }

    double totalPrice()
    {
    double total = 0;
    for (int i = 0; i < bookedProduct.size(); i++) {
        total += bookedProduct[i]->getPrice();
    }
    return total;
    }
};
int main()
{
  // 1. Tạo sản phẩm bình thường
    Product* p1 = new Product("Book", 50, 101);
    p1->displayInfo();

    // 2. Tạo sản phẩm điện tử
    Electronic* e1 = new Electronic("Laptop", 1000, 201, "Dell");
    e1->displayInfo();

    // 3. Cộng thêm giá cho book bằng operator+
    Product* p2 = new Product(*p1 + 20); // giá mới = 70
    p2->displayInfo();

    // 4. Tạo giỏ hàng
    ShoppingCart cart("MyCart");

    // 5. Thêm sản phẩm vào giỏ hàng
    cart.addItem(p1);
    cart.addItem(e1);
    cart.addItem(p2);

    // 6. Hiển thị giỏ hàng
    cart.showCart();

    // 7. Tính tổng giá
    cout << "Total price in cart: $" << cart.totalPrice() << endl << endl;

    // 8. Giảm giá 10% cho Laptop
    e1->applyDiscountable(10); // giá mới = 900
    cout << "After 10% discount on Laptop:" << endl;
    cart.showCart();
    cout << "Total price in cart: $" << cart.totalPrice() << endl << endl;

    cout << "Total price in cart: $" << cart.totalPrice() << endl;

    // Giải phóng bộ nhớ
    delete p1;
    delete p2;
    delete e1;

    return 0;

}

