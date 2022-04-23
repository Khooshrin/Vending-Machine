#include <iostream>
#include <bits/stdc++.h>
#include <map>
using namespace std;

int main()
{

    //Vector which stores details of items in the vending machine

    vector <pair<string,pair<int,pair<int,int>>>> items={
        {"Lays",{1,{10,20}}},{"Kurkure",{2,{10,10}}},{"Cheetos",{3,{10,15}}},
        {"Hershey",{4,{10,100}}},{"Kitkat",{5,{10,30}}},{"Mars",{6,{10,5}}},
        {"Coke",{7,{10,35}}},{"Sting",{8,{10,25}}},{"Appy",{9,{10,80}}}
    };

    int choice=0;
    map<int,int> money;

    //Map which stores the denomination of notes along with their quantities

    money.insert(pair<int, int>(5,10));
    money.insert(pair<int, int>(10,10));
    money.insert(pair<int, int>(20,10));
    money.insert(pair<int, int>(50,10));
    money.insert(pair<int, int>(100,10));

    while(choice!=8)
    {
        cout << "\nEnter choice:\n1) Buy Items \n2) Refill Items \n3) Refill Money\n4) Add denominations\n5) Remove Items\n6) Remove Denominations\n7) Add Items\n8) Exit\n";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {

                //Map to store the itemcode and the quantity of items the user wishes to buy
                map<int,int> order;

                while(true)
                {

                    //Displaying items currently available in vending machine

                    cout<<"Description\tID\tQuantity\tPrice\n";
                    for(int i=0;i<items.size();i++)
                    {
                        cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                    }
                    cout<<"\n\nEnter Item ID and Quantity for each item you want to purchase.\nWhen done please enter -1.\n\n";
                    int itemCode=0,quantity=0;
                    while(true)
                    {
                        cin >> itemCode;
                        if(itemCode==-1)
                            break;
                        else
                        {
                            cin >> quantity;

                            //Checking if the item has already been purchased by the user in the same order

                            if(order.find(itemCode)!=order.end())
                                cout<<"This item has already been purchased.\n";
                            else
                            {
                                bool check=false;
                                //Checking if itemID enetered is valid
                                for(int i=0;i<items.size();i++)
                                {
                                    if (items[i].second.first==itemCode)
                                    {
                                        check=true;
                                        break;
                                    }
                                }
                                if(check==false)
                                {
                                    cout << "Invalid Item ID\n";
                                    continue;
                                }

                                //If slot is empty
                                if(items[itemCode-1].second.second.first==0)
                                {
                                    cout << "There is no stock for this item.\nCannot buy the item.\n";
                                    continue;
                                }

                                //If quantity enetered by user exceeds quantity present in machine
                                while(quantity>items[itemCode-1].second.second.first)
                                {
                                    cout << "Quantity you wish to purchase exceeds quantity in Vending Machine.\nQuantity Available: "<<items[itemCode-1].second.second.first<<endl;
                                    cout << "If you wish to change your amount please re-enter the quantity else if you do not want to buy this item enter -1\n";
                                    cin >> quantity;
                                }
                                if(quantity==-1)
                                    continue;                                
                                else
                                    order.insert(pair<int,int>(itemCode,quantity));
                            }
                        }
                    }
                    if(order.empty()==false)
                    {

                        //Displaying the order of the user to confirm

                        cout << "\nYour order is below.\nDescription\tItem ID \tQuantity\n";
                        map<int, int>::iterator itr;
                        for(itr=order.begin();itr!=order.end();++itr)
                            cout << items[itr->first-1].first << "\t\t" << itr->first << "\t\t" << itr->second << endl;
                        int confirm=-2;
                        cout << "Please confirm your order. Enter 1 to confirm, 0 to redo the order or -1 to exit." << endl;
                        cin >> confirm;
                        if(confirm==-1)
                            return 0;
                        else if(confirm==0)
                        {
                            //Clearing order and allowing user to re-order
                            order.clear();
                            continue;
                        }
                        int cost=0;
                        //Reducing quantity of item in vending machine and calculating total cost
                        for(itr=order.begin();itr!=order.end();++itr)
                        {
                            items[itr->first-1].second.second.first=items[itr->first-1].second.second.first-itr->second;
                            cost=cost+itr->second*items[itr->first-1].second.second.second;
                        }
                        cout << "\nFinal Price to Pay: " << cost << endl;
                        cout << "\nThe machine accepts only certain denominations.\nPlease enter number of notes of each denomination you wish to pay with.\n";
                        int amt=0;

                        //Map to store the denomination and the number of notes of each denomination the user pays with
                        map<int,int> pay;

                        //Accepting money from user in denominations accepted by the machine

                        while(true)
                        {
                            for(itr=money.begin();itr!=money.end();++itr)
                            {
                                cout << "Enter the number of notes of the denomination Rs." << itr->first << endl;
                                cin >> amt;
                                pay.insert(pair<int,int>(itr->first,amt));
                            }
                            amt=0;

                            //Calculating total cost paid by user
                            for(itr=pay.begin();itr!=pay.end();++itr)
                            {
                                amt=amt+itr->first*itr->second;
                            }

                            //If user paid money less than the cost
                            if(amt<cost)
                            {
                                cout << "Full amount not paid.\nPayment Amount Remaining:" << (cost-amt) << "\nPlease take your money back and re-enter your payment amount.\n"; 
                                pay.clear();
                                continue;
                            }
                            else
                            {
                                //Increasing the quantity of notes of denominations paid by user
                                for(itr=pay.begin();itr!=pay.end();++itr)
                                {
                                    map<int,int> :: iterator it = money.find(itr->first);
                                    it->second=it->second+itr->second;
                                }
                                break;
                            }
                        }

                        //Calculating change that has to be returned and returning it in appropriate denominations present in the machine
                        if(amt>cost)
                        {
                            int chng=amt-cost;

                            //Map to store the denomination and the number of notes of each denomination that the user will receive as change
                            map<int,int> change;

                            for(auto itr=money.rbegin();itr!=money.rend();++itr)
                            {
                                if((int)(chng/itr->first)!=0 && (int)(chng/itr->first)<=itr->second)
                                {
                                    change.insert(pair<int,int>(itr->first,(int)(chng/itr->first)));
                                    map<int,int> :: iterator it = money.find(itr->first);
                                    it->second=it->second-(chng/itr->first);
                                    chng=chng-((int)((chng/itr->first)))*itr->first;
                                }
                                else if((int)(chng/itr->first)!=0 && (int)(chng/itr->first)>itr->second)
                                {
                                    change.insert(pair<int,int>(itr->first,itr->second));
                                    chng=chng-(itr->first)*(itr->second);
                                    itr->second=0;
                                }
                            }
                            if(chng==0)
                            {
                                cout << "\nPayment Accepted.\nPlease accept your change.\nDenomination\tNumber of Notes\n";
                                for(itr=change.begin();itr!=change.end();++itr)
                                {
                                    cout << itr->first << "\t\t" << itr->second << endl;
                                }
                                cout << "\nThank you for using the Vending Machine.\n";
                                break;
                            }
                            else
                            {
                                //If the vending machine does not have enough change
                                cout << "\nNot enough change in the machine.\nPlease take your money back.\nYour order has been cancelled.";
                                for(itr=pay.begin();itr!=pay.end();++itr)
                                {
                                    map<int,int> :: iterator it = money.find(itr->first);
                                    it->second=it->second-itr->second;
                                }
                                for(itr=order.begin();itr!=order.end();++itr)
                                {
                                    items[itr->first-1].second.second.first=items[itr->first-1].second.second.first+itr->second;
                                }
                                break;
                            }
                        }
                        else
                        {
                            //If amount paid is equal to cost
                            cout << "Payment Accepted.\nNo change has to be returned.\nThank you for using the Vending Machine.\n";
                            break;
                        }
                    }
                    else
                        break;
                } 
            }
                break;
            case 2:
            {

                //Map to store the items codes and the quantity the user wishes to re-stock
                map<int,int> restock;

                while (true)
                {

                    //Displaying items currently available in vending machine

                    cout << "Displaying the current stocks of items :\n";
                    cout<<"Description\tID\tQuantity\tPrice\n";
                    for(int i=0;i<9;i++)
                    {
                        cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                    }
                    cout<<"Enter item ID of item you want to restock and quantity by which you want to restock\nWhen done please enter -1.\n\n";
                    int itemCode=0,restockQuantity=0;
                        while(true)
                        {
                            cin >> itemCode;
                            if(itemCode==-1)
                                break;
                            else
                            { 
                                cin >> restockQuantity;
                                //If slot does not contain any items
                                if(items[itemCode-1].first=="EMPTY")
                                    cout << "This slot is empty.\nPlease add item before refill.\n";
                                else if(itemCode>=1 && itemCode<=9)
                                {
                                    //If the quantity is equal to the maximum capacity
                                    if(items[itemCode-1].second.second.first==10)
                                    {
                                        cout << "This item is at max capacity, cannot restock.\n";
                                    }
                                    else if(restockQuantity+items[itemCode-1].second.second.first<=10)
                                    {
                                        //Updating quantity in machine
                                        items[itemCode-1].second.second.first = items[itemCode-1].second.second.first + restockQuantity;
                                        restock.insert(pair<int,int>(itemCode,restockQuantity));
                                    }
                                    else
                                    {
                                        //If quantity after re-fill exceeds maximum capacity
                                        while((restockQuantity+items[itemCode-1].second.second.first)>10)
                                        {
                                            cout << "Quantity you wish to restock exceeds the maximum capacity of the item chosen.\nThe max capacity for the chosen item is 10. Current quantity: "<<items[itemCode-1].second.second.first<<endl;
                                            cout << "If you wish to change the quantity please re-enter the quantity or else enter -1\n";
                                            cin >> restockQuantity;
                                            if(restockQuantity==-1)
                                                   continue;
                                            else
                                            {
                                                //Updating quantity in machine
                                                items[itemCode-1].second.second.first = items[itemCode-1].second.second.first + restockQuantity;
                                                restock.insert(pair<int,int>(itemCode,restockQuantity));
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                    cout << "Invalid Item ID\n";
                            }
                        }
                
                    if(restock.empty()==false)
                    {
                        //Displaying re-stock request
                        cout << "\nYour restock request is below.\nDescription\tItem ID \tQuantity\n";
                        map<int, int>::iterator itr;
                        for(itr=restock.begin();itr!=restock.end();++itr)
                            cout << items[itr->first-1].first << "\t\t" << itr->first << "\t\t" << itr->second << endl;
                        int confirm=-2;
                        cout << "Please confirm your order. Enter 1 to confirm, 0 to redo the order or -1 to exit." << endl;
                        cin  >> confirm;
                        
                        if(confirm==-1)
                            break;
                        else if(confirm==0)
                        {
                            //setting quantities back to before re-stock and allowing user to redo order
                            for(itr=restock.begin();itr!=restock.end();++itr)
                                items[itr->first-1].second.second.first = items[itr->first-1].second.second.first - itr->second;
                            restock.clear();
                            continue;
                        }
                        
                        cout << "\nThe updated stock is below.\nDescription\tItem ID \tQuantity\n";
                        
                        //Displaying updated stock
                        for(int i=0;i<9;i++)
                        {
                            cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                        }
                       break;
                       cout << "Thank you for using the Vending Machine.\n";

                    }
                    else
                    break;

                }
            }
            break;
            case 3: 
            {
                //Displaying current denominations and quantities

                cout << "Denominations\tNumber of Notes\n";
                map<int, int>::iterator itr;
                for(itr=money.begin();itr!=money.end();++itr)
                {
                    cout << itr->first << "\t\t" << itr->second << endl;;
                }
                cout << "\nThe machine accepts only certain denominations.\nPlease enter number of notes of each denomination you wish to add in the machine\n" << endl;
                int num=0;
                map<int, int>::iterator itr1;
                for(itr1=money.begin();itr1!=money.end();)
                {
                    //If the machine already contains enough notes of a denomination
                    if(itr1->second>=10)
                    {
                        cout << "The machine has sufficient notes of Rs." << itr1->first << endl;
                        itr1++;
                        continue;
                    }

                    //Calculating maximum number of notes the machine will accept during re-fill
                    int nons=(itr1->second>=10)? 0 : (10-itr1->second);
                    cout << "You can add " << nons << " notes of the denomination Rs." << itr1->first << endl;
                    cout << "Enter the number of notes you wish to add of the denomination Rs." << itr1->first << endl;
                    cin >> num;

                    //If amount to restock exceeds limit of number of notes to re-fill
                    if(num>nons)
                    {
                        cout << "The total number of notes exceeds the limit. Please re-enter appropriate amount.\n";
                    }
                    else
                    {
                        itr1->second+=num;
                        itr1++;
                    }
                }

                //Displaying updated money in the vending machine
                cout << "\nDenominations\tNumber of Notes\n";
                map<int, int>::iterator itr2;
                for(itr2=money.begin();itr2!=money.end();++itr2)
                {
                    cout << itr2->first << "\t\t" << itr2->second << endl;;
                }
                cout << "\nThank You! Money Updated!";
            }
            break;
            case 4:
            {
                //Displaying current denominations and quantities
                cout << "Current Denominations:\n";
                map<int,int>::iterator itr;
                for(itr=money.begin();itr!=money.end();++itr)
                {
                    cout << itr->first << endl;
                }

                cout << "Enter Denominations and Quantity you wish to add. Enter -1 when done.\n";

                //Map to store the new denominations along with the quantity of notes
                map<int,int> den;

                int denomination=0,quantity=0,confirm = -2;
                while(denomination!=-1)
                {
                    cin >> denomination;
                    if(denomination==-1)
                    {
                        if(den.empty()==false)
                        {

                            //Displaying denomination and quantity of notes the user wants to add
                            cout << "Denominations\tNumber of Notes\n";
                            for(itr=den.begin();itr!=den.end();++itr)
                            {
                                cout << itr->first << "\t\t" << itr->second << endl;
                            }

                            //Confirming the order
                            int confirm=-1;
                            cout << "Enter 1 to confirm or 0 to cancel.\n";
                            cin >> confirm;
                            if(confirm==1)
                            {
                               for(itr=den.begin();itr!=den.end();++itr)
                                {
                                    //Adding new denominations and their quantities to the machine
                                    money.insert(pair<int,int>(itr->first,itr->second));
                                } 

                                //Displaying updated money in the vending machine
                                cout << "Denominations have been added to machine.\nUpdated Money:\n";
                                for(itr=money.begin();itr!=money.end();++itr)
                                {
                                    cout << itr->first << "\t\t" << itr->second << endl;
                                } 
                            }
                        }
                        else
                            cout << "You do not wish to add any denomination.\n" << endl;
                        break;
                    }
                    else
                    {
                        cin >> quantity;
                        bool check=false;
                        for(itr=money.begin();itr!=money.end();++itr)
                        {
                            //If the denomination the user wishes to add is already present in the machine
                            if(denomination==itr->first)
                            {
                                cout << "The Vending Machine already has this denomination.\n";
                                check=true;
                                break;
                            }
                        }

                        //If the quantity of the notes the user wishes to add exceeds 10
                        while(quantity>10)
                        {
                            cout << "The maximum number of notes is 10.\nKindly re-enter quantity or -1 if you do not want to add this denomination.\n";
                            cin >> quantity;
                            if(quantity==-1)
                                break;
                        }
                        if(check==false && quantity>=0 && quantity<=10)
                            den.insert(pair<int,int>(denomination,quantity));
                    }
                }
            }
            break;
            case 5:
            {   
                //Vector to store the itemID of the items the user wants to remove
                vector<int> dlt;
                int itemCode=0;      

                //Displaying current item stock
                cout << "Current items stock:\n";
                cout<<"Description\tID\tQuantity\tPrice\n";
                for(int i=0;i<items.size();i++)
                {
                    cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                }
                cout << "Enter itemID of item you want to remove:\nEnter - 1 when done\n";       
                while (true) 
                {
                    cin >> itemCode;
                    if(itemCode==-1)
                    {
                        if(dlt.empty()==false)
                        {

                            //Displaying item codes of items the user wishes to remove
                            cout<<"Item Code of Items to be cleared\n";
                            for(int i=0;i<dlt.size();i++)
                            {
                                cout<<dlt[i]<<endl;
                            }   

                            //Confirming order with user
                            int confirm=-2;
                            cout << "Enter 1 to confirm your action, 0 to redo and -1 to exit\n";
                            cin >> confirm;
                            if(confirm==-1)
                                break;
                            else if(confirm==0)
                            {
                                //Clearing the vector to remove the current order and allowing the user to re-order
                                dlt.clear();
                                cout << "Current items stock:\n";
                                cout<<"Description\tID\tQuantity\tPrice\n";
                                for(int i=0;i<items.size();i++)
                                {
                                    cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                                }
                                cout << "Enter itemID of item you want to clear:\nEnter - 1 when done\n";
                                continue;                             
                            }

                            //for all items the user wishes to delete, empty their slots
                            for(auto it1 = dlt.begin(); it1!=dlt.end();++it1)
                            {
                                for(auto it2=items.begin(); it2!=items.end();++it2)
                                {
                                    if(*it1==it2->second.first)
                                    {
                                        items[*it1-1].first="EMPTY";
                                        items[*it1-1].second.second.first=0;
                                        items[*it1-1].second.second.second=0;
                                        break;
                                    }
                                }
                            }

                            //Displaying the updated vending machine
                            cout<<"Updated Items in Vending Machine:\nDescription\tID\tQuantity\tPrice\n";
                            for(int i=0;i<items.size();i++)
                            {
                                cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                            }
                            cout << "Thank you for using the Vending Machine.\n";
                            break;
                        }
                        else
                            break;
                    }
                    else
                    {
                        if(itemCode>=1 && itemCode<=9)
                        {
                            //Checking if the user has already enetered this item code to delete
                            if(find(dlt.begin(),dlt.end(),itemCode)==dlt.end())
                                dlt.push_back(itemCode);
                            else
                                cout << "You have already entered this value\n";
                        }
                        else 
                            cout << "Invalid Item Code\n";                        
                    }
                }
            }
            break;
            case 6:
            {

                //Displaying the current denominations and their quantities in the vending machine
                cout << "Current Deoniminations:\nDenominations\tNumber of Notes\n";
                map<int,int>::iterator itr;
                for(itr=money.begin();itr!=money.end();++itr)
                {
                    cout << itr->first << "\t\t" << itr->second << endl;
                }

                cout << "Enter Denominations you wish to remove.\nEnter -1 when done.\n";
                int den=0;

                //Vector to store the item code of items the user wishes to delete from the vending machine
                vector<int> rem;

                while(den!=-1)
                {
                    cin >> den;
                    if(den==-1)
                    {
                        if(rem.empty()==false)
                        {
                            //Displaying order to remove denominations and confirming it
                            cout << "Please Confirm the denominations you wish to remove.\nEnter 1 to continue or 0 to cancel.\n";
                            for(int i=0;i<rem.size();i++)
                            {
                                cout << rem[i] << endl;
                            }
                            int confirm=-1;
                            cin >> confirm;
                            if(confirm==0)
                                break; 
                            else if(confirm==1)
                            {
                                for(int i=0;i<rem.size();i++)
                                {
                                    //Removing the denomination from the vending machine
                                    money.erase(rem[i]);
                                }

                                //Displaying current denominations in the vending machine
                                cout << "Current Deoniminations:\nDenominations\tNumber of Notes\n";
                                for(itr=money.begin();itr!=money.end();++itr)
                                {
                                    cout << itr->first << "\t\t" << itr->second << endl;
                                }
                                cout << "Denominations Successfully Removed.\nThank you for using the Vending Machine.\n";
                                break;
                            }
                        }
                        else
                            cout << "You do not want to remove any denomination.\n";
                    }

                    //Checking if the denomination the user wishes to delete exists in the machine or not
                    if(money.find(den)==money.end())
                    {
                        cout << "The machine does not have this denomination.\n";
                    }
                    else
                        rem.push_back(den);
                }
            }
            break;
            case 7:
            {

                //Displaying the current item stock in the vending machine
                cout << "Current items stock:\n";
                cout<<"Description\tID\tQuantity\tPrice\n";
                for(int i=0;i<items.size();i++)
                {
                    cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                }

                //Accepting item code of item user wishes to add
                cout << "Enter itemID of item you want to add:\nEnter - 1 to cancel.\n";
                int itemCode,quantity,price;
                string desc;
                cin >> itemCode;
                if(itemCode==-1)
                    break;
                if(items[itemCode-1].first!="EMPTY")    //If the slot is not empty, item cannot be added as it already contains items
                    cout << "This slot contains items.\nItems cannot be added to this slot.\n" ;
                else
                {
                    cout << "Please enter item description, quantity and price.\n";
                    cin >> desc >> quantity >> price;

                    //if the quantity of the item the user wishes to add exceeds the maximum capacity of an item in the machine
                    while(quantity>10)
                    {
                        cout << "Maximum quantity of an item is 10.\nPlease re-enter a quantity or -1 to cancel.\n";
                        cin >> quantity;
                    }
                    if(quantity==-1)
                        break;

                    //Adding the new item to the slot in the vending machine
                    items[itemCode-1].first=desc;
                    items[itemCode-1].second.second.first=quantity;
                    items[itemCode-1].second.second.second=price;

                    //Displaying the updated stock of items in the vending machine
                    cout << "Updated items stock:\n";
                    cout<<"Description\tID\tQuantity\tPrice\n";
                    for(int i=0;i<items.size();i++)
                    {
                        cout<<items[i].first<<"\t\t"<<items[i].second.first<<"\t"<<items[i].second.second.first<<"\t\t"<<items[i].second.second.second<<endl;
                    }
                }
            }
            break;
            case 8:
            return 0;
            break;
            default:
            cout << "Invalid Option.\nPlease enter again.\n";        
        }
    }
    return 0;
}