#include <iostream>

int main(void)
{
    using namespace std;
    cout << "Please enter one of the folowing choices: \n";
    cout << "c) carnivore " << '\t';
    cout << "p) pianist "   << endl;
    cout << "t) tree "      << '\t';
    cout << "g) game "      << endl;
    cout << ": ";

    char ch;
    cin.get(ch).get();
    while (ch){
        switch(ch){
            case 'c' :
                cout << "C maple is a carnivore(:" << endl;
                break;
            case 'p' :
                cout << "P maple is a pianist(:"   << endl;
                break;
            case 't' :
                cout << "T maple is a tree(:"      << endl;
                break;
            case 'g' :
                cout << "G maple is a game(:"      << endl;
                break;
            default :
                cout << "Please enter a c, p, t, or g:";
                ch = 'q';
        }
        //if (ch == 'c' || ch == 'p' || ch == 't' || ch == 'g') 
        if (ch != 'q')
            break;
        cin >> ch;
    }

    return 0;
}
