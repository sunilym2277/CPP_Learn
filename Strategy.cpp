#include <iostream>
using namespace std;

// 1. Strategy Interface
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

// 2. Concrete Strategies
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) override { cout << "Paid " << amount << " using Credit Card.\n"; }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay(int amount) override { cout << "Paid " << amount << " using PayPal.\n"; }
};

// 3. Context
class ShoppingCart {
    PaymentStrategy* paymentMethod;
public:
    void setPaymentMethod(PaymentStrategy* method) { paymentMethod = method; }
    void checkout(int amount) { if(paymentMethod) paymentMethod->pay(amount); }
};

// 4. Client
int main() {
    ShoppingCart cart;

    CreditCardPayment creditCard;
    PayPalPayment paypal;

    cart.setPaymentMethod(&creditCard);
    cart.checkout(500);  // Paid 500 using Credit Card.

    cart.setPaymentMethod(&paypal);
    cart.checkout(1200); // Paid 1200 using PayPal.

    return 0;
}
