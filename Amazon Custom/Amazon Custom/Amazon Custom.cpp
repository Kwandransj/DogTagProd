#include <fstream>
#include <iostream>
#include<string>
using namespace std;
void produce_column(void);
void produce_inv(void);

int main()
{
    produce_column();

    

}
void produce_column(void) {
    string prev_prev_line;
    string prev_line;
    string cur_line;
    string order_id;
    string asin;
    string sku;
    string pet_name = " ";
    string line1 = " ";
    string line2 = " ";
    string line3 = " ";
    string line4 = " ";
    bool id_found = false;
    bool asin_found = false;
    bool tag_complete = false;
    bool check_nums = false;
    int name_counter = 0;
    int start_index = 1;
    int lines_found = 0;

    ifstream inFile;

    //file path of pdf read file
    //***CHANGE***//
    //use double slashes in file path
    inFile.open("C:\\Users\\bryan\\OneDrive\\Desktop\\Pdf-To-Column\\amazon.txt");
    ofstream csvfile;
   
    //file path of csv write file
    //***CHANGE***//
    csvfile.open("C:\\Users\\bryan\\OneDrive\\Desktop\\Pdf-To-Column\\copy.txt", std::ofstream::out | std::ofstream::trunc);
    
    if (!inFile) {
        cerr << "Unable to open";
        exit(1);
    }
    if (!csvfile) {
        cerr << "Unable to open";
        exit(1);
    }
    

    


    inFile >> cur_line;
    while (!inFile.eof()) {
        while (!tag_complete) {

            //cout << cur_line << "\n";
            if (prev_line == "ID:" && !id_found) {
                order_id = cur_line;
            }

            if (prev_line == "ASIN:") {
                asin = cur_line;
            }

            if (prev_line == "SKU:") {
                sku = cur_line;
            }

            if (prev_line == "Name:" && prev_prev_line == "Pet") {
                pet_name = cur_line;
                while (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                    prev_prev_line = prev_line;
                    prev_line = cur_line;
                    inFile >> cur_line;

                    if (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                        pet_name += " ";
                        pet_name += cur_line;
                    }
                }
            }
            if (prev_line == "1:") {
                line1 = cur_line;
                lines_found++;
                while (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                    prev_prev_line = prev_line;
                    prev_line = cur_line;
                    inFile >> cur_line;

                    if (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                        line1 += " ";
                        line1 += cur_line;
                    }
                }
            }
            if (prev_line == "2:") {
                line2 = cur_line;
                lines_found++;
                while (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                    prev_prev_line = prev_line;
                    prev_line = cur_line;
                    inFile >> cur_line;

                    if (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                        line2 += " ";
                        line2 += cur_line;
                    }
                }
            }
            if (prev_line == "3:") {
                line3 = cur_line;
                lines_found++;
                while (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                    prev_prev_line = prev_line;
                    prev_line = cur_line;
                    inFile >> cur_line;

                    if (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                        line3 += " ";
                        line3 += cur_line;
                    }
                }
            }
            if (prev_line == "4:") {
                line4 = cur_line;
                lines_found++;
                while (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                    prev_prev_line = prev_line;
                    prev_line = cur_line;
                    inFile >> cur_line;

                    if (cur_line != "Line" && cur_line != "Grand" && cur_line != "1" && cur_line != "2") {
                        line4 += " ";
                        line4 += cur_line;
                    }
                }
            }

            if (prev_line == "Seller.\"" || (prev_line == "1" && check_nums) || (prev_line == "2" && check_nums)) {
                tag_complete = true;

            }
            if (prev_line == "1" && !check_nums) {
                check_nums = true;

            }
            if (prev_line == "2" && !check_nums) {
                check_nums = true;

            }





            prev_prev_line = prev_line;
            prev_line = cur_line;

            inFile >> cur_line;
        }
        csvfile << "Order ID: # " << order_id << "\n";
        csvfile << "A" << start_index << "\n\n\n";
        csvfile << "ASIN: " << asin << "\n";
        csvfile << "SKU: " << sku << "\n";
        csvfile << "Customizations:\n";
        csvfile << "Text:\n";
        csvfile << "Font Name: Arial\n";
        csvfile << "Font Color: Black (#000)\n";
        csvfile << "Pet Name: " << pet_name << "\n";
        csvfile << "Line 1: " << line1 << "\n";
        csvfile << "Line 2: " << line2 << "\n";
        csvfile << "Line 3: " << line3 << "\n";
        csvfile << "Line 4: " << line4 << "\n";

        csvfile << "\n";

        lines_found = 0;
        tag_complete = false;
        id_found = false;
        check_nums = false;

        order_id = "";
        asin = "";
        sku = "";
        pet_name = " ";
        line1 = " ";
        line2 = " ";
        line3 = " ";
        line4 = " ";
        start_index++;
    }


    cout << "done\n";
}
void produce_inv()
{
    string cur_line;
    string prev_line;

    ifstream inFile;
    ifstream invIn;

    string inv[30][3];



    inFile.open("C:\\Users\\bryan\\OneDrive\\Desktop\\Pdf-To-Column\\amazon.txt");
    invIn.open("C:\\Users\\bryan\\OneDrive\\Desktop\\Pdf-To-Column\\data\\invnames.txt");

    for (int i = 0; i < 30; i++) {
        invIn >> inv[i][0];
    }
    for (int i = 0; i < 30; i++) {
        invIn >> inv[i][1];
    }
    for (int i = 0; i < 30; i++) {
        inv[i][2] = "0";
    }










    ofstream inventory;


    inventory.open("C:\\Users\\bryan\\OneDrive\\Desktop\\Pdf-To-Column\\inventory.csv", std::ofstream::out | std::ofstream::trunc);
    if (!inFile) {
        cerr << "Unable to open";
        exit(1);
    }
    if (!inventory) {
        cerr << "Unable to open";
        exit(1);
    }

    inFile >> cur_line;
    cout << cur_line;

    inventory << "Color,Size,# of Tags\n";
    string sku;
    while (!inFile.eof()) {
        if (prev_line == "SKU:") {
            sku = cur_line;
            if (sku == "BK-XS") {
                inv[0][2] = to_string(std::stoi(inv[0][2]) + 1);
            }
            if (sku == "BK-S") {
                inv[1][2] = to_string(std::stoi(inv[1][2]) + 1);
            }
            if (sku == "BK-M") {
                inv[2][2] = to_string(std::stoi(inv[2][2]) + 1);
            }
            if (sku == "BK-ML") {
                inv[3][2] = to_string(std::stoi(inv[3][2]) + 1);
            }
            if (sku == "BK-L") {
                inv[4][2] = to_string(std::stoi(inv[4][2]) + 1);
            }
            if (sku == "BK-XL") {
                inv[5][2] = to_string(std::stoi(inv[5][2]) + 1);
            }
            if (sku == "W-XS") {
                inv[6][2] = to_string(std::stoi(inv[6][2]) + 1);
            }
            if (sku == "W-S") {
                inv[7][2] = to_string(std::stoi(inv[7][2]) + 1);
            }
            if (sku == "W-M") {
                inv[8][2] = to_string(std::stoi(inv[8][2]) + 1);
            }
            if (sku == "W-ML") {
                inv[9][2] = to_string(std::stoi(inv[9][2]) + 1);
            }
            if (sku == "W-L") {
                inv[10][2] = to_string(std::stoi(inv[10][2]) + 1);
            }
            if (sku == "W-XL") {
                inv[11][2] = to_string(std::stoi(inv[11][2]) + 1);
            }
            if (sku == "G-XS") {
                inv[12][2] = to_string(std::stoi(inv[12][2]) + 1);
            }
            if (sku == "G-S") {
                inv[13][2] = to_string(std::stoi(inv[13][2]) + 1);
            }
            if (sku == "G-M") {
                inv[14][2] = to_string(std::stoi(inv[14][2]) + 1);
            }
            if (sku == "G-ML") {
                inv[15][2] = to_string(std::stoi(inv[15][2]) + 1);
            }
            if (sku == "G-L") {
                inv[16][2] = to_string(std::stoi(inv[16][2]) + 1);
            }
            if (sku == "G-XL") {
                inv[17][2] = to_string(std::stoi(inv[17][2]) + 1);
            }
            if (sku == "O-XS") {
                inv[18][2] = to_string(std::stoi(inv[18][2]) + 1);
            }
            if (sku == "O-S") {
                inv[19][2] = to_string(std::stoi(inv[19][2]) + 1);
            }
            if (sku == "O-M") {
                inv[20][2] = to_string(std::stoi(inv[20][2]) + 1);
            }
            if (sku == "O-ML") {
                inv[21][2] = to_string(std::stoi(inv[21][2]) + 1);
            }
            if (sku == "O-L") {
                inv[22][2] = to_string(std::stoi(inv[22][2]) + 1);
            }
            if (sku == "O-XL") {
                inv[23][2] = to_string(std::stoi(inv[23][2]) + 1);
            }
            if (sku == "P-XS") {
                inv[24][2] = to_string(std::stoi(inv[24][2]) + 1);
            }
            if (sku == "P-S") {
                inv[25][2] = to_string(std::stoi(inv[25][2]) + 1);
            }
            if (sku == "P-M") {
                inv[26][2] = to_string(std::stoi(inv[26][2]) + 1);
            }
            if (sku == "P-ML") {
                inv[27][2] = to_string(std::stoi(inv[27][2]) + 1);
            }
            if (sku == "P-L") {
                inv[28][2] = to_string(std::stoi(inv[28][2]) + 1);
            }
            if (sku == "P-XL") {
                inv[29][2] = to_string(std::stoi(inv[29][2]) + 1);
            }
        }

        prev_line = cur_line;
        inFile >> cur_line;
    }
    for (int i = 0; i < 30; i++) {
        inventory << inv[i][0] << "," << inv[i][1] << "," << inv[i][2] << "\n";
    }
}


