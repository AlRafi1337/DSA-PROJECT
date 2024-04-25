// Group Members 
//Name:ABDULLAH AL RAFI
//NAME:UMAIR
//NAME:MOHSIN
// Name : Marzouq Hashmi


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <ios>

using namespace std;

//Class delcared to hold data and pointer of node 
class PizzaNode {
public:
    //Pizza ID
    int id;
    //Pizza name
    string name;
    //Pizza price
    float price;
    // Pointer to the next Pizza 
    PizzaNode* next;
    PizzaNode() {
        name = "";
        price = 0.0;
        next = NULL;
    }
    PizzaNode(string n, float p) {
        name = n;
        price = p;
        next = NULL;
    }
};
//Class declared to hold a queue of pizza
class PizzaQueue{
    private:
        PizzaNode* head;
        PizzaNode* tail;
    public:
        PizzaQueue(){
            head = NULL;
            tail = NULL;
        }
        void DeleteQueue(void) {
            PizzaNode* currNode = head, * nextNode = NULL;
            while (currNode != NULL) {
                nextNode = currNode->next;
                delete currNode;
                currNode = nextNode;
            }
            head = NULL;
            tail = NULL;
        }
        bool IsEmpty() {
            return head == NULL;
        }
        PizzaNode* Add_Order(int i,string n,float p){
            PizzaNode* newNode = new PizzaNode;
            newNode->id = i; newNode->name = n; newNode->price = p;
            if(head == NULL){
                newNode->next = head;
                head = tail = newNode;
            }else{
                newNode->next = NULL;
                tail->next = newNode;
                tail = newNode;
            }
            return newNode;
        }
        void Delete_Pizza(){
            PizzaNode* temp = head;
            head = head->next;
            temp->next = NULL;
            delete temp;
            if(head == NULL){
                tail = NULL;
            }
        }
        PizzaNode* Get_Front(){
            PizzaNode* tempNode = new PizzaNode;
            tempNode = head;
            return tempNode;
        }
        PizzaNode* Get_Back(){
            PizzaNode* tempNode = new PizzaNode;
            tempNode = tail;
            return tempNode;
        }
        void List_Out_Pizzas(void){
            PizzaNode* currNode = head;
            if(currNode == NULL){
                cout << "List is Empty\n";
            }else{
                while (currNode != NULL) {
                cout <<left << "[" << setw(2) << currNode->id <<  "]" << setw(10) << currNode->name << " " << setw(6) << currNode->price << endl;
                currNode = currNode->next;
                }
            }
        }
        float Get_Total_Price(){
            PizzaNode* currNode = head;
            float total = 0.0;
            if(head != NULL){
                while(currNode != NULL){
                total += currNode->price;
                currNode = currNode->next;
                }
            }
            return total;
        }
        void Show_Order() {
            cout << "----------------------" << endl
                << "        ORDER         " << endl
                << "----------------------" << endl;
            List_Out_Pizzas();
            cout << "----------------------" << endl;
            cout << " Total : " << Get_Total_Price() << endl;
            cout << "----------------------" << endl;
        }
        int get_file_size(fstream &f){
            int begin = f.tellp(); 
            f.seekp(0, ios::end);
            int size = f.tellp();
            f.seekp(begin, ios::beg);
            return size;
        }
        void Sales(){
            fstream fout("Sales.txt", ios::out| ios::app);
            PizzaNode* currNode = Get_Front();
            if (fout.is_open()) {
                if(get_file_size(fout) == 0){
                    fout << currNode->id << currNode->name << "` " << currNode->price;
                    Delete_Pizza();
                    currNode = Get_Front();
                }
                while (currNode != NULL) {
                    fout << endl << currNode->id << currNode->name << "` " << currNode->price;
                    Delete_Pizza();
                    currNode = Get_Front();
                }
                fout.close();
            }
        }
        void Write_to_file(string file_name) {
            fstream fout(file_name.c_str(), ios::out);
            PizzaNode* currNode = head;
            if (fout.is_open()) {
                while (currNode != NULL) {
                    fout << currNode->id << currNode->name << "` " << currNode->price;
                    currNode = currNode->next;
                    if (currNode != NULL) {
                        fout << endl;
                    }
                }
                fout.close();
            }
        }
        void Finish_Order(){
            string custname;
            cout << "Enter your Full Name (No Spaces): ";
            cin >> custname;
            custname = "Ord_" + custname + ".txt";
            fstream fout("Order_list.txt", ios::app);
            fout << custname << endl;
            fout.close();
            Write_to_file(custname);
            Sales();
        }
};
//Class delcared to hold a list of pizza
class PizzaList {
private:
    PizzaNode* head;
    
public:
    PizzaList(void) {
        head = NULL;
    }
    void Delete_PizzaList(void) {
        if (head != NULL) {
            PizzaNode* currNode = head, * nextNode = NULL;
            while (currNode != NULL) {
                nextNode = currNode->next;
                delete currNode;
                currNode = nextNode;
            }
            head = NULL;
        }
    }
    bool IsEmpty() {
        return head == NULL;
    }
    bool Pizza_Check(int id) {
        PizzaNode* currnode = head;
        int currIndex = 1;
        while ((currnode) && (currnode->id != id)) {
            currnode = currnode->next;
            currIndex++;
        }
        if (currnode) {
            return true;
        }
        else {
            return false;
        }
    }
    string Get_Name(int id) {
        PizzaNode* currNode = head;
        while (currNode != NULL) {
            if (id == currNode->id) {
                return currNode->name;
            }
            else {
                currNode = currNode->next;
            }
        }
        return "";
    }
    float Get_Price(int id) {
        PizzaNode* currNode = head;
        while (currNode != NULL) {
            if (id == currNode->id) {
                return currNode->price;
            }
            else {
                currNode = currNode->next;
            }
        }
        return 0;
    }
    PizzaNode* Add_Order(int i, string n, float p) {
        int currIndex = 0;
        PizzaNode* currNode = head;
        PizzaNode* prevNode = NULL;
        //Sort the Pizza by ID
        while (currNode && i > currNode->id) {
            prevNode = currNode;
            currNode = currNode->next;
            currIndex++;
        }
        PizzaNode* newNode = new PizzaNode;
        newNode->id = i;
        newNode->name = n;
        newNode->price = p;

        if (currIndex == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
        return newNode;
    }
    PizzaNode* Insert_New_Pizza(int i, string n, float p) {
        int currIndex = 0;
        PizzaNode* currNode = head;
        PizzaNode* prevNode = NULL;
        //Sort the Pizza by ID
        while (currNode && i > currNode->id) {
            prevNode = currNode;
            currNode = currNode->next;
            currIndex++;
            if (currNode != NULL) {
                if (currNode->id == i) {
                    return NULL;
                }
            }
        }
        PizzaNode* newNode = new PizzaNode;
        newNode->id = i;
        newNode->name = n;
        newNode->price = p;

        if (currIndex == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
        return newNode;
    }
    PizzaNode* Get_Pizza(int id) {
        PizzaNode* currNode = head;
        while (currNode != NULL) {
            if (id == currNode->id) {
                return currNode;
            }
            else {
                currNode = currNode->next;
            }
        }
        currNode = NULL;
        return currNode;
    }
    void Change_Pizza_Price(float new_price, int id) {
        PizzaNode* currNode = Get_Pizza(id);
        if (currNode != NULL) {
            currNode->price = new_price;
        }
    }
    int Find_Pizza(string n) {
        PizzaNode* currnode = head;
        int currIndex = 1;
        while ((currnode) && (currnode->name != n)) {
            currnode = currnode->next;
            currIndex++;
        }
        if (currnode) {
            return currnode->id;
        }
        else {
            return 0;
        }
    }
    void Delete_Pizza(int id) {
        PizzaNode* prevNode = NULL;
        PizzaNode* currNode = head;
        while (currNode && currNode->id != id) {
            prevNode = currNode;
            currNode = currNode->next;
        }
        if (currNode) {
            if (prevNode) {
                prevNode->next = currNode->next;
                delete currNode;
            }
            else {
                head = currNode->next;
                delete currNode;
            }

        }
    }
    void List_Out_Pizzas(void) {
        PizzaNode* currNode = head;
        if (currNode == NULL) {
            cout << "List is Empty\n";
        }
        else {
            while (currNode != NULL) {
                cout << left << "[" << setw(2) << currNode->id << "] "  << currNode->name << " " << setw(6) << currNode->price << endl;
                currNode = currNode->next;
            }
        }
    }
    void Write_to_file(string file_name) {
        fstream fout(file_name.c_str(), ios::out);
        PizzaNode* currNode = head;
        if (fout.is_open()) {
            while (currNode != NULL) {
                fout << currNode->id << currNode->name << "` " << currNode->price;
                currNode = currNode->next;
                if (currNode != NULL) {
                    fout << endl;
                }
            }
            fout.close();
        }
    }
    void Read_from_file(string file_name) {
        fstream fin(file_name.c_str(), ios::in);
        if (fin.is_open()) {
            if (!(fin.peek() == std::ifstream::traits_type::eof())) {
                while (!fin.eof()) {
                    int id;
                    string name;
                    float price;
                    fin >> id;
                    getline(fin, name, '`');
                    fin >> price;
                    Insert_New_Pizza(id, name, price);
                }
                fin.close();
            }
        }
    }
    float Get_Total_Price(){
        PizzaNode* currNode = head;
        float total = 0.0;
        if(head != NULL){
            while(currNode != NULL){
            total += currNode->price;
            currNode = currNode->next;
            }
        }
        return total;
    }
    void Show_Order() {
        cout << "----------------------" << endl
            << "        ORDER         " << endl
            << "----------------------" << endl;
        List_Out_Pizzas();
        cout << "----------------------" << endl;
        cout << " Total : " << Get_Total_Price() << endl;
        cout << "----------------------" << endl;
    }
    void Show_Menu() {
        cout << "----------------------" << endl
            << "         MENU         " << endl
            << "----------------------" << endl;
        List_Out_Pizzas();
        cout << "----------------------" << endl
            << "[1] Pepperoni Set" << endl
            << "[2] Veggie Set" << endl
            << "[3] Party Set" << endl
            << "----------------------" << endl;
    }
    void Read_Order(){
        string order_name[20];
        fstream fin("Order_list.txt", ios::in);
        if(fin.is_open()){
            cout << "----------------------" << endl
                 << "List of Pending Orders" << endl
                 << "----------------------" << endl;
            int counter = 0;
            while(!fin.eof() && counter <= 19){
                fin >> order_name[counter];
                if(order_name[counter] == ""){
                    break;
                }
                cout << "[" << counter+1 << "] " << order_name[counter] << endl;
                counter++;
            }
            fin.close();
            cout << "----------------------" << endl;
            int order_num;
            cout << "Enter Order No : ";
            cin >> order_num;
            Read_from_file(order_name[order_num-1]);
            Show_Order();
        }
    }
    void Generate_Sales_Report(){
        fstream fin("Sales.txt", ios::in);
        if (fin.is_open()) {
            if (!(fin.peek() == std::ifstream::traits_type::eof())) {
                while (!fin.eof()) {
                    int id;
                    string name;
                    float price;
                    fin >> id;
                    getline(fin, name, '`');
                    fin >> price;
                    Add_Order(id, name, price);
                }
                fin.close();
            }
            PizzaNode* currNode = head;
            PizzaNode* prevNode = head;
            int count = 0;
            cout << "------------------------------------------------------------------------" << endl;
            cout << setw(4) << "ID" << setw(30) << "NAME" << setw(10) << "PRICE" << setw(10) << "AMOUNT" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            while(currNode != NULL){
                while((currNode != NULL) && (prevNode->id == currNode->id)){
                    count++;
                    currNode = currNode->next;
                }
                cout << "[" <<  setw(2) << prevNode->id << "]" << setw(30) << prevNode->name << setw(10) << prevNode->price << setw(10) << count << endl;
                count = 0;
                prevNode = currNode;
            }
            cout << "------------------------------------------------------------------------" << endl;
            cout << "Total Sales : " << Get_Total_Price() << endl;
            cout << "------------------------------------------------------------------------" << endl;
        }
    }
};
// View for staff
void Staff_Menu_Choice() {
    // List out the options for the staff menu
    cout << "----------------------" << endl
        << "      DSA PIZZA       " << endl
        << "----------------------" << endl
        << "  [1] Add Pizza" << endl
        << "  [2] Delete Pizza" << endl
        << "  [3] Pizza List" << endl
        << "  [4] Find Pizza" << endl
        << "  [5] Change Price" << endl
        << "  [6] Show Order List" << endl
        << "  [7] Show Sales " << endl
        << "  [8] Exit" << endl
        << "----------------------" << endl;
}

void Staff_View(PizzaList pizlist) {
    // define the exit contition
    while (true) {
        int choice = 0;
        Staff_Menu_Choice();
        cout << "INPUT :";
        cin >> choice;
        //Add a pizza to the menu
        if (choice == 1) {
            system("CLS");
            int piz_id; // new pizza id
            string piz_name;// new pizza name
            float piz_price;// new pizzas price
            cout << "ID :";
            cin >> piz_id;
            cin.ignore();
            cout << "NAME :";
            getline(cin, piz_name);
            cout << "PRICE :";
            cin >> piz_price;
            pizlist.Insert_New_Pizza(piz_id, piz_name, piz_price);
        }
        // Delete a pizza
        else if (choice == 2) {
            system("CLS");
            int piz_id;
            cout << "ID :";
            cin >> piz_id;
            pizlist.Delete_Pizza(piz_id);
            cout << "ID : " << piz_id << " Pizza Deleted \n";
        }
        // Show the list of pizza
        else if (choice == 3) {
            system("CLS");
            pizlist.List_Out_Pizzas();
        }
        // find a certain pizza
        else if (choice == 4) {
            system("CLS");
            string search;
            cout << "Enter the name of Pizza to be found\n INPUT :";
            cin.ignore();
            getline(cin, search);
            int found = pizlist.Find_Pizza(search);
            if (found == 0) {
                cout << "Not Found\n";
            }
            else {
                cout << "Found \n ID :" << found << endl;
            }
        }
        // change the price of an existing pizza
        else if (choice == 5) {
            system("CLS");
            int id;
            float price;
            cout << "ID :";
            cin >> id;
            cout << "NEW PRICE :";
            cin >> price;
            pizlist.Change_Pizza_Price(price, id);
        }
        // show the list of orders
        else if (choice == 6) {
            system("CLS");
            PizzaList temp;
            temp.Read_Order();
        }
        // show the sales report
        else if (choice == 7) {
            system("CLS");
            PizzaList Salesreport;
            Salesreport.Generate_Sales_Report();
        }
        // Exit Staff terminal
        else if (choice == 8) {
            break;
        }
        else {
            // give out to if there is an incorrect input
            cout << "Please Enter a valid optional\n";
        }
    }
    pizlist.Write_to_file("PizzaList.txt");
    system("CLS");
    cout << "\n---Staff terminal terminated---\n";
}

void Customer_Menu_Choice() {
    // List out the options for the staff menu
    cout << "----------------------" << endl
        << "      DSA PIZZA       " << endl
        << "----------------------" << endl
        << "  [1] Menu" << endl
        << "  [2] Add Set" << endl
        << "  [3] Add Pizza" << endl
        << "  [4] Find Pizza" << endl
        << "  [5] Show Order" << endl
        << "  [6] Done" << endl
        << "  [7] Exit" << endl
        << "----------------------" << endl;
}


void Customer_View(PizzaList &pizlist) {
    // define the exit contition
    PizzaQueue orderlist;
    while (true) {
        int choice = 0;
        Customer_Menu_Choice();
        cout << "INPUT :";
        cin >> choice;
        // Show Menu
        if (choice == 1) {
            system("CLS");
            pizlist.Show_Menu();
        }
        // Add set to order
        else if (choice == 2) {
            system("CLS");
            pizlist.Show_Menu();
            cout<< "----------------------" << endl
                << "       ADD SET        " << endl
                << "----------------------" << endl;
            int choice_set = 0;
            cout << "INPUT :";
            cin >> choice_set;
            if (choice_set == 1) {
                orderlist.Add_Order(1, pizlist.Get_Name(1), pizlist.Get_Price(1));
                orderlist.Add_Order(4, pizlist.Get_Name(4), pizlist.Get_Price(4));
            }
            else if (choice_set == 2) {
                orderlist.Add_Order(5, pizlist.Get_Name(5), pizlist.Get_Price(5));
                orderlist.Add_Order(6, pizlist.Get_Name(6), pizlist.Get_Price(6));
            }
            else if (choice_set == 3) {
                orderlist.Add_Order(1, pizlist.Get_Name(1), pizlist.Get_Price(1));
                orderlist.Add_Order(2, pizlist.Get_Name(2), pizlist.Get_Price(2));
                orderlist.Add_Order(3, pizlist.Get_Name(3), pizlist.Get_Price(3));
                orderlist.Add_Order(4, pizlist.Get_Name(4), pizlist.Get_Price(4));
            }
            else {
            }
            orderlist.Show_Order();
        }
        // Add pizza to order
        else if (choice == 3) {
            system("CLS");
            pizlist.Show_Menu();
            cout<< "----------------------" << endl
                << "       ADD PIZZA      " << endl
                << "----------------------" << endl;
            int choice_piz;
            cout << "INPUT :";
            cin >> choice_piz;
            if (pizlist.Pizza_Check(choice_piz)) {
                string newname = pizlist.Get_Name(choice_piz);
                float newprice = pizlist.Get_Price(choice_piz);
                orderlist.Add_Order(choice_piz, newname, newprice);
            }
            orderlist.Show_Order();
        }
        // Search for pizza
        else if (choice == 4) {
            system("CLS");
            string search;
            cout << "Enter the name of Pizza to be found\n INPUT :";
            cin.ignore();
            getline(cin, search);
            int found = pizlist.Find_Pizza(search);
            if (found == 0) {
                cout << "Not Found\n";
            }
            else {
                cout << "Found \n ID :" << found << endl;
            }
        }
        // show order
        else if (choice == 5) {
            system("CLS");
            orderlist.Show_Order();
        }
        // Order Complete
        else if (choice == 6) {
            orderlist.Finish_Order();
            break;
        }
        // exit
        else if (choice == 7) {
            break;
        }
        else {
            cout << "Please enter a valid option\n";
        }
    }
    system("CLS");
    cout << "---Customer Terminal Terminated---\n";
}

int main() {
    PizzaList ListofPizza;
    ListofPizza.Read_from_file("PizzaList.txt");
    int choice = 0;
    cout << "[1] Staff Terminal\n[2] Customer Terminal\n[3] Exit \nINPUT :";
    cin >> choice;
    if (choice == 1) {
        Staff_View(ListofPizza);
    }
    else if (choice == 2) {
        Customer_View(ListofPizza);
    }
    else {
        cout << "\nExit\n";
    }
    ListofPizza.Delete_PizzaList();
    return 0;
}