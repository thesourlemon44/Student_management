//Janerys M. Ortiz Aviles (Y00631857)
//Emanuel Rivera Hernandez (Y00652428)

#include <iostream>
#include <string>
#include <fstream> //Para guardar los datos
#include <cstdlib> //Para numeros random (ID)
#include <set> //Para guardar los ID y que no se repitan
#include <iomanip> 


using namespace std;

set<string>save_id; //Guardar los IDs

//Para que el usuario seleccione (menos errores)
string campus_select() {
    string selected_campus;
    int sel;
    string campus[8] = { "Metropolitan", "Fajardo", "Bayamon", "Arecibo", "Barranquita",
                         "Ponce", "Guayama", "San German" };

    do {
        cout << "Select Campus: \n";
        for (int i = 0; i < 8; i++) {
            cout << i + 1 << ". " << campus[i] << "\n";
        }
        cin >> sel;
        cin.ignore();
        if (sel >= 1 && sel <= 8) {
            selected_campus = campus[sel - 1];
        }
        else {
            system("cls");
            cout << "INVALID INPUT" << "\n";
        }
    } while (sel < 1 || sel > 8);
    return selected_campus;
}

//Para que el usuario selecciones (menos errores)
string major_select() {
    string selected_major;
    int sel;
    string major[9] = { "Business Admin.", "Communications", "Science & Math.",
                      "Arch. Eng.", "Mech. Eng.", "Indust. Eng.",
                      "Elect. Eng.", "Human. Studies", "Compu. Science" };

    do {
        cout << "Select Major: \n";
        for (int i = 0; i < 9; i++) {
            cout << i + 1 << ". " << major[i] << "\n";
        }
        cin >> sel;
        cin.ignore();
        if (sel >= 1 && sel <= 9) {
            selected_major = major[sel - 1];


        }
        else {
            system("cls");
            cout << "INVALID INPUT \n";
        }

    } while (sel < 1 || sel > 9);
    return selected_major;
}




void studentrmv(string&studentID) {
    //removes student from system
    ifstream MyFile("Record.txt");
    ofstream File("NewRecord.txt");
    bool studentfound = false;
    string line;
    while (getline(MyFile, line)) {

        if (line.find(studentID) != string::npos) {
            studentfound = true;
            getline(MyFile, line);
            continue;
        }
        File << line << endl;
    }
    MyFile.close();
    File.close();
    remove("Record.txt");
    rename("NewRecord.txt", "Record.txt");

    if (studentfound) {
        cout << studentID << " has been succesfully been deleted\n";
    }
    else {
        cout << studentID << " is already not in the system\n";
    }

}




void studentadd() {
    //adds a student to the system

    string name, apellido, city, phone, major, recinto, email, studentID;

    cout << "=================================================================\n";
    cout << "|| Please provide the following information of the new student ||\n";
    cout << "=================================================================\n";
    cout << "Student ID: ";
    cin >> studentID; 
    cin.ignore(); //si no esta, brinca

    //Validacion ID
    while (save_id.count(studentID) > 0) {
        cout << "This student ID is already taken \n";
        cout << "Please enter a new student ID: ";
        cin >> studentID; 
        cin.ignore();
    }
    save_id.insert(studentID); 

    cout << "Name: ";
    getline(cin, name);
    cout << "Last name: ";
    getline(cin, apellido);
    cout << "Phone number: ";
    getline(cin, phone);
    cout << "Email: ";
    getline(cin, email);
    cout << "\nMayor: \n";
    major = major_select();
    cout << "City: ";
    getline(cin, city);

    cout << "\nCampus: \n";
    recinto = campus_select();

    ofstream MyFile("Record.txt", ios::app);
    // Edit file
    MyFile << left;
    MyFile << "||" << setw(15) << studentID
           << "||" << setw(15) << name
           << "||" << setw(15) << apellido
           << "||" << setw(15) << phone
           << "||" << setw(25) << email
           << "||" << setw(15) << major
           << "||" << setw(15) << city
           << "||" << setw(15) << recinto
           << "||" << endl;

    MyFile << setfill('=') << setw(148) << "=" << endl;
    MyFile.close();

}




void report() {
    //shows ONLY the students in the system
    ifstream MyFile("Record.txt");


    string line;
    while (getline(MyFile, line)) {
        cout << line << endl;
    }
    MyFile.close();
}




int main()
{
    char opc_menu;
    char opc_addstud, opc_rmv;
    string num_estudiante;
    cout << "=================================================================\n";
    cout << "||        ADVANCED      PROCASTINATION      INSTITUTE          ||\n";
    cout << "=================================================================\n\n";

    do { //Loop para que el menu 
        cout << "--------------------MENU--------------------\n";
        cout << "Choose an option of the following menu: \n";
        cout << "1- Add new students \n";
        cout << "2- Remove students \n";
        cout << "3- View records \n";
        cout << "4- Exit program \n";
        cout << "-------------------------------------------- \n";
        cout << "Enter option: ";
        cin >> opc_menu;
        cout << "\n\n";
        cin.ignore();
        //Switch case para el menu
        switch (opc_menu) {
        case '1':
            system("cls");
            do { //Loop para que el usuario pueda ingresar mas estudiantes sin tener que volver al menu
                cout << "=================================================================\n";
                cout << "||                         NEW STUDENT                         ||\n";
                cout << "=================================================================\n\n";
                studentadd();
                cout << "Do you wish to add more students? Y/N: \n";
                cin >> opc_addstud;
            } while (opc_addstud == 'Y' || opc_addstud == 'y');
            break;
        case '2':
            do { //Loop para que el usuario pueda remover estudiantes
                system("cls");
                cout << "=================================================================\n";
                cout << "||                     REMOVE STUDENT                          ||\n";
                cout << "=================================================================\n\n";

                cout << "Please enter the student ID: ";
                cin >> num_estudiante; 

                studentrmv(num_estudiante);
                cout << "Do you wish to remove/delete more students Y/N: \n";
                cin >> opc_rmv;
            } while (opc_rmv == 'Y' || opc_rmv == 'y');
            break;
        case '3':
            system("cls");
            cout << "=================================================================\n";
            cout << "||                           REPORT                            ||\n";
            cout << "=================================================================\n\n";
            report();
            break;

        case '4':
            system("cls");
            cout << "Thanks for using the program \n";
            break;
        default:
            system("cls");
            cout << "INVALID INPUT \n";
        }

    } while (opc_menu != '4');
    cout << "\n-------------------------------------------- \n";


    return 0;
}
