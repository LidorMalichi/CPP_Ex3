#include <iostream>
#include <vector>
#include <string>


using namespace std;

int main() {
    
    cout << "                     02            04            06" <<endl;
    string s = "/      \\";
    string s2 = "                  ";
    string s4 = "      ";
    
    cout << s2 + s +s4 +s +s4 + s<<endl;
    cout << "              01            03            05            07" <<endl;
    cout<< ""<<endl;
    
    cout << "              ||   Fld(03)  ||   Mou(02)  ||   Hil(12)  ||" <<endl;
    cout<< ""<<endl;
    cout << "              09            11            13            15" <<endl;
    
    string s3 = "           ";
    cout << s3 + s + s4 + s + s4 + s + s4 + s<<endl;
    cout << "       08            10            12            14            16" <<endl;
    cout<< ""<<endl;
    cout << "       ||   Fld(03)  ||   Mou(02)  ||   Hil(12)  ||   Pas(08)  ||" <<endl;
    cout << "" <<endl;
    cout << "       18            20            22            24            26" <<endl;
    string s5 = "    ";
    cout << s5 + s + s4 + s + s4 + s + s4 + s + s4 +s<<endl;
    cout << "17            19            23            25            27            29" <<endl;
    cout << "" <<endl;
    cout << "||   Fld(03)  ||   Mou(02)  ||   Hil(12)  ||   Pas(08)  ||   Des(00)  ||" <<endl;
    cout << "" <<endl;
    cout << "28            30            32            34            36            38" <<endl;
    string s6 = "\\      /";
    cout << s5 + s6 + s4 + s6 + s4 + s6 + s4 + s6 + s4 + s6<<endl;
    cout << "       29            31            33            35            37" <<endl;
    cout << "" <<endl;
    cout << "       ||   hil(03)  ||   Mou(02)  ||   Fil(12)  ||   Pas(08)  ||" <<endl;
    cout << "" << endl;
    cout << "       39            41            43            45            47" <<endl;
    cout << s3 + s6 + s4 + s6 + s4 + s6 + s4 + s6 <<endl;
    cout << "              40            42            44            46" <<endl;
    cout << "" <<endl;
    cout << "              ||  Flds(03)  ||   Mou(02)  ||   Hil(12)  ||" <<endl;
    cout << "" <<endl;
    cout << "              48            50            52            54" <<endl;
    cout << s2 + s6 + s4 + s6 + s4 + s6 <<endl;
    cout << "                     49            51            53" <<endl;
    return 0;
}
