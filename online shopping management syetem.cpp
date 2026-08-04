#include <iostream>
#include <string>
using namespace std;

//--------------- Global Variables ----------------//

string name, email, city;
int customerType;

string productNames[8] = {
    "T-Shirt",
    "Jeans",
    "Shoes",
    "Watch",
    "Handbag",
    "Headphones",
    "Mobile Cover",
    "Perfume"
};

float prices[8] = {
    1200, 3500, 5000, 2500,
    4200, 3000, 700, 2800
};

// Cart arrays (maximum 20 items)
int cartProductIds[20];      // Stores product IDs
int cartQuantities[20];      // Stores quantities
int cartItemCount = 0;       // Number of items in cart

float total = 0;
float gst = 0;
float delivery = 0;
float customerDiscount = 0;
float orderDiscount = 0;
float paymentCharges = 0;
float finalAmount = 0;

//--------------- Functions ----------------//

// Register User
void registerUser()
{
    
 cout << "\n========== USER REGISTRATION ==========\n";
    cout << "Enter Your Name: ";
    getline(cin, name);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter City: ";
    getline(cin, city);

    cout << "\nCustomer Type\n";
    cout << "1. New Customer\n";
    cout << "2. Returning Customer\n";
    cout << "Enter Choice: ";
    cin >> customerType;
}

// Display Products
void displayProducts()
{
    cout << "\n========== PRODUCT LIST ==========\n";
    cout << "ID\tProduct\t\t\tPrice\n";
    cout << "----------------------------------------\n";
    for(int i=0; i<8; i++)
    {
       
               
        cout << (i+1) << "\t"  << productNames[i] << "\t\t\tRs. " << prices[i]<< endl;
    }
}

// Add Product
void addToCart()
{
    if (cartItemCount == 20)
    {
        cout << "Cart is full! Cannot add more items.\n";
        return;
    }

    displayProducts();

    int productId, quantity;

    cout << "\nEnter product ID (1-8): ";
    cin >> productId;

    if (productId < 1 || productId > 8)
    {
        cout << "Invalid product ID!\n";
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity < 1)
    {
        cout << "Quantity must be positive!\n";
        return;
    }

    cartProductIds[cartItemCount] = productId - 1;
    cartQuantities[cartItemCount] = quantity;
    cartItemCount++;

    cout << "Added " << quantity << " "
         << productNames[productId - 1]
         << "(s) to cart!\n";
}

// Product Total (Pointer Used)
float calculateTotal()
{
    total = 0;

    float *ptr = prices;

    for(int i=0; i<cartItemCount; i++)
    {
         int productIndex = cartProductIds[i];
        int quantity = cartQuantities[i];
        
        // Using pointer to access price
        float* pricePtr = & prices[productIndex];
        total += (*pricePtr) * quantity;
    }

    return total;
}

// GST
float calculateGST()
{
    return total * 0.17;
}

// Delivery Charges
float calculateDelivery()
{
    if(city=="Lahore" || city=="Karachi" || city=="Islamabad")
        return 250;

    return 500;
}

// Customer Discount
float calculateCustomerDiscount()
{
    if(customerType==1)
        return total*0.05;

    return total*0.10;
}

// Order Discount
float calculateOrderDiscount()
{
    if(total>=5000 && total<=10000)
        return total*0.05;

    if(total>10000)
        return total*0.12;

    return 0;
}

// Payment Charges
float calculatePaymentCharges()
{
    int method;

    cout << "\nPayment Method\n";
    cout << "1. Cash On Delivery\n";
    cout << "2. Debit/Credit Card\n";
    cout << "Enter Choice: ";
    cin >> method;

    if(method==2)
        return (total+gst+delivery-customerDiscount-orderDiscount)*0.025;

    return 0;
}

// View User Details
void viewUser()
{
    cout << "\n========== USER DETAILS ==========\n";

    cout << "Name : " << name << endl;
    cout << "Email: " << email << endl;
    cout << "City : " << city << endl;

    if(customerType==1)
        cout << "Customer Type: New Customer\n";
    else
        cout << "Customer Type: Returning Customer\n";
}

// Display Bill
void displayBill()
{
    total = calculateTotal();
    gst = calculateGST();
    delivery = calculateDelivery();
    customerDiscount = calculateCustomerDiscount();
    orderDiscount = calculateOrderDiscount();
    paymentCharges = calculatePaymentCharges();

    finalAmount = total + gst + delivery + paymentCharges
                  - customerDiscount - orderDiscount;

    cout << "\n\n========== ONLINE SHOPPING BILL ==========\n";

    cout << "User Name: " << name << endl;
    cout << "City: " << city << endl;

    if(customerType==1)
        cout << "Customer Type: New Customer\n";
    else
        cout << "Customer Type: Returning Customer\n";

    cout << "\nProduct Total      : Rs. " << total << endl;
    cout << "GST (17%)          : Rs. " << gst << endl;
    cout << "Delivery Charges   : Rs. " << delivery << endl;
    cout << "Customer Discount  : Rs. " << customerDiscount << endl;
    cout << "Order Discount     : Rs. " << orderDiscount << endl;
    cout << "Payment Charges    : Rs. " << paymentCharges << endl;

    cout << "-------------------------------------------\n";
    cout << "Final Amount       : Rs. " << finalAmount << endl;
    cout << "Thank You For Shopping :)\n";
    cout << "===========================================\n";
}

//---------------- Main Function ----------------//

int main()
{
    int choice;
cout << "\n========================================\n";
    cout << "   WELCOME TO SHOPPING CART SYSTEM   \n";
    cout << "========================================\n";
    
    registerUser();

    do
    {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. View Products\n";
        cout << "2. Add Product To Cart\n";
        cout << "3. Calculate Checkout Bill\n";
        cout << "4. View User Details\n";
        cout << "5. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayProducts();
                break;

            case 2:
                addToCart();
                break;

            case 3:
                if(cartItemCount==0)
                {
                    cout << "\nCart is Empty!\n";
                }
                else
                {
                    displayBill();
                }
                break;

            case 4:
                viewUser();
                break;

            case 5:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    }while(choice!=5);

    return 0;
}
