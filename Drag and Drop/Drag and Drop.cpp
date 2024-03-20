#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>
#include <locale>
#include <algorithm>
#include <array>
#include <ctime>



using namespace std;
void produce_column(void);
void produce_tag(string order_id, string asin, string sku, string pet_name, string line1, string line2, string line3, string line4, bool line1found, bool line2found, bool line3found, bool line4found, int lines_found, int start_index, bool website, bool quantity);
unsigned int num_Variations = 42;


vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
};



std::ofstream csvfile;
std::ofstream script;
std::ofstream automate;
char hang[] = { 'Q','q',',','(',')','@' };
std::vector<std::vector<std::string>> orangeBasic_data;
std::vector<std::vector<std::string>> blue_data;
std::vector<std::vector<std::string>> orange_data;
std::vector<std::vector<std::string>> grey_data;
std::vector<std::vector<std::string>> white_data;
std::vector<std::vector<std::string>> black_data;
std::vector<std::vector<std::string>> pink_data;
std::vector<int> variations;
std::vector<std::string> sizes;


std::vector<std::vector<std::vector<std::string>>> datavec;
string month;
string mon;
struct tm* timeinfo;

string wpath = "";
string apath = "";


std::vector<std::vector<std::string> > parsedCsv;
std::vector<std::vector<std::string> > heights;

int orange = 0;
int white = 0;
int black = 0;
int grey = 0;
int pink = 0;
int blue = 0;
int orangeBasic = 0;
string color;
int number;
bool run_amazon = false;
bool run_website = false;
bool hasEnding(std::string const& fullString, std::string const& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else {
        return false;
    }
}
bool containsOnlyASCII(const std::string& filePath) {
    for (auto c : filePath) {
        if (static_cast<unsigned char>(c) > 127) {
            return false;
        }
    }
    return true;
}


void list_dir(const char* path) {
    string fname;
    bool found_file = false;
    struct dirent* entry;
    int files_found = 0;
    int pdfCount = 0;
    int csvCount = 0;
    bool err = false;

    while (!found_file) {
        DIR* dir = opendir(path);

        if (dir == NULL) {
            cout << "Error: Directory does not exist\n";
            cin.ignore();
        }
        while ((entry = readdir(dir)) != NULL) {
            fname = entry->d_name;

            if (fname.front() != '.') {
                files_found++;
                if (hasEnding(fname, ".pdf")) {
                    apath = fname;
                    pdfCount++;
                    run_amazon = true;
                }
                if (hasEnding(fname, ".csv")) {
                    wpath = fname;
                    csvCount++;
                    run_website = true;
                }
                if (pdfCount > 1) {
                    cout << "Error: Too many pdf files found upload only 1 file and press enter to try again\n";
                    err = true;
                    run_amazon = false;
                }
                if (csvCount > 1) {
                    cout << "Error: Too many csvfiles found upload only 1 file and press enter to try again\n";
                    err = true;
                    run_website = false;
                }
            }

        }
        closedir(dir);


        if (csvCount == 0) {
            cout << "No website file found\n";
        }
        if (pdfCount == 0) {
            cout << "No amazon file found\n";
        }
        if (csvCount == 0 && pdfCount == 0) {
            err = true;
        }

        if (err) {
            found_file = false;
            err = false;
            pdfCount = 0;
            csvCount = 0;
            files_found = 0;
            cin.ignore();
        }
        else {
            found_file = true;
        }



    }
    return;
}
int main(int argc, char* argv[]) {

bool debug_Mode = false;

    if (argc > 1) {
        if (argv[1] == "true") {
            bool debug_Mode = true;
        }
    }
    

    // strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
    // std::string str(buffer);

    // std::cout << str;



    variations.resize(num_Variations + 1);
    datavec.resize(num_Variations + 1);
    for (unsigned int i = 0; i < variations.size(); i++) {
        variations.at(i) = 1;
    }
    sizes.push_back("XS");
    sizes.push_back("S");
    sizes.push_back("M");
    sizes.push_back("ML");
    sizes.push_back("L");
    sizes.push_back("XL");
    produce_column();




    return 0;
}

void produce_column(void) {

    time_t rawtime;
    
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    
    if (timeinfo->tm_mon == 0) {
        month = "january";
        mon = "1";
    }
    else if (timeinfo->tm_mon == 1) {
        month = "febuary";
        mon = "2";
    }
    else if (timeinfo->tm_mon == 2) {
        month = "march";
        mon = "3";
    }
    else if (timeinfo->tm_mon == 3) {
        month = "april";
        mon = "4";
    }
    else if (timeinfo->tm_mon == 4) {
        month = "may";
        mon = "5";
    }
    else if (timeinfo->tm_mon == 5) {
        month = "june";
        mon = "6";
    }
    else if (timeinfo->tm_mon == 6) {
        month = "july";
        mon = "7";
    }
    else if (timeinfo->tm_mon == 7) {
        month = "august";
        mon = "8";
    }
    else if (timeinfo->tm_mon == 8) {
        month = "september";
        mon = "9";
    }
    else if (timeinfo->tm_mon == 9) {
        month = "october";
        mon = "10";
    }
    else if (timeinfo->tm_mon == 10) {
        month = "november";
        mon = "11";
    }
    else if (timeinfo->tm_mon == 11) {
        month = "december";
        mon = "12";
    }
    
    string basepath = "M:\\DogCollarTagProduction\\ActiveEngraving";
    string path = "M:\\DogCollarTagProduction\\ActiveEngraving\\" + month + "\\" + mon + "-" + to_string(timeinfo->tm_mday);
    if (debug_Mode == true) {
        cout << apath << " " << wpath << "\n";
    }
    list_dir(path.c_str());
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
    bool tag_complete = false;
    bool check_nums = false;
    int start_index = 0;
    int lines_found = 0;
    int tags_in_order = 0;
    bool line1found = false;
    bool line2found = false;
    bool line3found = false;
    bool line4found = false;

    ifstream inFile;

    //file path of pdf read file
    //***CHANGE***//
    //use double slashes in file path


    //ofstream csvfile;





    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
    std::string str(buffer);

    /*std::cout << str << "\n";*/

    string fname = path + "\\" + str + "-copy_column.txt";
    string sname = path + "\\" + str + "-script.scr";
    char outname[1024];
    char soutname[1024];
    strcpy_s(outname, fname.c_str());
    strcpy_s(soutname, sname.c_str());
    csvfile.open(outname);
    script.open(soutname);
    std::ofstream engrave(path + "\\" + str +"engrave.csv");

    automate.open(path + "\\auto.ahk");
    automate << "inc = 1" << "\n";
    automate << "color = 3" << "\n";
    automate << "size = 1" << "\n";
    automate << "sizeinc = 1" << "\n";

    automate << "curpos = 3.35" << "\n";
    automate << "global dist := 0" << "\n";
    automate << "bignudge = 0.1" << "\n";
    automate << "spacing = 0.035" << "\n";


    automate << "XL()\n";
    automate << "{" << "\n";
    automate << "\tdist := 1.9" << "\n";
    automate << "}" << "\n";

    automate << "L()\n";
    automate << "{" << "\n";
    automate << "\tdist := 1.6" << "\n";
    automate << "}" << "\n";

    automate << "ML()\n";
    automate << "{" << "\n";
    automate << "\tdist := 1.3" << "\n";
    automate << "}" << "\n";

    automate << "M()\n";;
    automate << "{" << "\n";
    automate << "\tdist := 1.175" << "\n";
    automate << "}" << "\n";

    automate << "S()\n";
    automate << "{" << "\n";
    automate << "\tdist := 1" << "\n";
    automate << "}" << "\n";

    automate << "XS()\n";
    automate << "{" << "\n";
    automate << "\tdist := 0.775" << "\n";
    automate << "}" << "\n";


    if (!inFile) {
        cerr << "Unable to open1";
        exit(1);
    }
    if (!csvfile) {
        cerr << "Unable to open2";
        exit(1);
    }



    std::ifstream  data(basepath + "\\click\\params1.csv");
    std::string line;

    while (std::getline(data, line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> parsedRow;
        while (lineStream >> std::ws)
        {
            std::string csvElement;

            if (lineStream.peek() == '"') {
                lineStream >> std::quoted(csvElement);
                std::string discard;
                std::getline(lineStream, discard, ',');
            }
            else {
                std::getline(lineStream, csvElement, ',');
            }
            parsedRow.push_back(csvElement);
        }

        parsedCsv.push_back(parsedRow);
    }

    std::ifstream  data1(basepath + "\\click\\TextHeight.csv");
    std::string lin;

    while (std::getline(data1, lin))
    {
        std::stringstream lineStream(lin);
        std::string cell1;
        std::vector<std::string> parsedRow1;
        while (lineStream >> std::ws)
        {
            std::string csvElement1;

            if (lineStream.peek() == '"') {
                lineStream >> std::quoted(csvElement1);
                std::string discard1;
                std::getline(lineStream, discard1, ',');
            }
            else {
                std::getline(lineStream, csvElement1, ',');
            }
            parsedRow1.push_back(csvElement1);
        }

        heights.push_back(parsedRow1);
    }



bool quantity;


    if (run_amazon) {
        string remove_path = basepath + "\\Amazon.pdf";
        if (remove(remove_path.c_str()) != 0)
            perror("Error deleting file");
        else
            puts("File successfully deleted");


        int result;
        string old = path + "\\" + apath;

        char oldname[1024];
        strcpy_s(oldname, old.c_str());

        result = rename(oldname, (basepath + "\\Amazon.pdf").c_str());
        if (result == 0)
            puts("File successfully renamed");
        else
            perror("Error renaming file");

        std::system(".\\pdftotext -layout amazon.pdf");


        inFile.open(basepath + "\\Amazon.txt");



        inFile >> cur_line;
        bool website = false;
        while (!inFile.eof()) {

            while (!tag_complete) {
                string quantity_Num;
                if (debug_Mode == true) cout << cur_line << "\n";
                if (inFile.eof()) break;
                if (debug_Mode == true) cout << cur_line << "\n";
                if (prev_line == "Totals" ) {
                    int quantityInt = atoi(cur_line.c_str());
                    if (debug_Mode == true) cout << quantityInt << "\n";
                    if (quantityInt > 1){
                        quantity = true;
                    }
                    else {
                        quantity = false;
                    }
                }
                if (prev_line == "ID:" && prev_prev_line == "Order") {
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
                    while (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                        prev_prev_line = prev_line;
                        prev_line = cur_line;
                        inFile >> cur_line;

                        if (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                            pet_name += " ";
                            pet_name += cur_line;
                        }
                    }
                }
                if (prev_line == "1:") {
                    line1 = cur_line;
                    lines_found++;
                    line1found = true;
                    while (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                        prev_prev_line = prev_line;
                        prev_line = cur_line;
                        inFile >> cur_line;

                        if (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                            line1 += " ";
                            line1 += cur_line;
                        }
                    }
                }
                if (prev_line == "2:") {
                    line2 = cur_line;
                    lines_found++;
                    line2found = true;
                    while (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                        prev_prev_line = prev_line;
                        prev_line = cur_line;
                        inFile >> cur_line;

                        if (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                            line2 += " ";
                            line2 += cur_line;
                        }
                    }
                }
                if (prev_line == "3:") {
                    line3 = cur_line;
                    lines_found++;
                    line3found = true;
                    while (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                        prev_prev_line = prev_line;
                        prev_line = cur_line;
                        inFile >> cur_line;

                        if (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                            line3 += " ";
                            line3 += cur_line;
                        }
                    }
                }
                if (prev_line == "4:") {
                    line4 = cur_line;
                    lines_found++;
                    line4found = true;
                    while (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                        prev_prev_line = prev_line;
                        prev_line = cur_line;
                        inFile >> cur_line;

                        if (cur_line != "Line" && cur_line != "Grand" && cur_line != "Returning" && cur_line != "1" && cur_line != "2") {
                            line4 += " ";
                            line4 += cur_line;
                        }
                    }
                }

                if (prev_line == "Ship") {// || (prev_line == "1" && check_nums) || (prev_line == "2" && check_nums)) {
                    tag_complete = true;

                    tags_in_order = 0;

                
                }
                
                if (prev_line == "Slide") {
                    tags_in_order++;
                    if (tags_in_order > 1) {
                        tag_complete = true;
                    }
                }
                if (prev_line == "1" && !check_nums) {
                    check_nums = true;

                }
                if (prev_line == "2" && !check_nums) {
                    check_nums = true;

                }
                if (cur_line == "2" && prev_prev_line == "Totals")
                    quantity = true;




                prev_prev_line = prev_line;
                prev_line = cur_line;

                inFile >> cur_line;

            }


            if (start_index != 0) {
                produce_tag(order_id, asin, sku, pet_name, line1, line2, line3, line4, line1found, line2found, line3found, line4found, lines_found, start_index, website, quantity);
            }

            lines_found = 0;

            check_nums = false;

            order_id = "";
            asin = "";
            sku = "";
            pet_name = " ";
            line1 = " ";
            line2 = " ";
            line3 = " ";
            line4 = " ";
            line1found = false;
            line2found = false;
            line3found = false;
            line4found = false;
            start_index++;
            tag_complete = false;
            quantity = false;
        }
        

        result = rename((basepath + "\\Amazon.pdf").c_str(), (path + "\\" + apath).c_str());
        if (result == 0)
            puts("File successfully renamed");
        else
            perror("Error renaming file");

        
    }

    if (run_website) {
        string webfname = path + "\\" + wpath;
        cout << webfname << "\n";


        std::ifstream  webdata(webfname);
        std::string webline;
        std::vector<std::vector<std::string> > webCsv;
        while (std::getline(webdata, webline))
        {
            std::stringstream lineStream(webline);
            std::string webcell;
            std::vector<std::string> webparsedRow;
            while (lineStream >> std::ws)
            {
                std::string webcsvElement;

                if (lineStream.peek() == '"') {
                    lineStream >> std::quoted(webcsvElement);
                    std::string webdiscard;
                    std::getline(lineStream, webdiscard, ',');
                }
                else {
                    std::getline(lineStream, webcsvElement, ',');
                }
                webparsedRow.push_back(webcsvElement);
            }

            webCsv.push_back(webparsedRow);
        }



        for (unsigned int i = 1; i < webCsv.size(); i++) {
            order_id = webCsv[i][0];
            asin = "website";
            sku = webCsv[i][2];
            
            if (sku == "") {
                break;
            }
            
            pet_name = webCsv[i][3];
            line1 = webCsv[i][4];
            line2 = webCsv[i][5];
            line3 = webCsv[i][6];
            line4 = webCsv[i][7];
            if (webCsv[i][1] != "1") {
                quantity = true;
            } else {
                quantity = false;
            }
            if (line1 != "" && line1 != "CHOOSE 1 LINE OR UP TO 5 LINES") {
                line1found = true;
                lines_found++;
            } else {
                line1found = false;
            }
            if (line2 != "" && line2 != "TEXT IS RECESSED, COLORED") {
                line2found = true;
                lines_found++;
            } else {
                line2found = false;
            }
            if (line3 != "" && line3 != "AND SIZED TO BEST FIT SPACE ") {
                line3found = true;
                lines_found++;
            } else {
                line3found = false;
            }
            if (line4 != "" && line4 != "*PREVIEW DOES NOT DISPLAY ACCURATE*") {
                line4found = true;
                lines_found++;
            } else {
                line4found = false;
            }
            if (debug_Mode == true) cout << sku << "\n";
        }
        webdata.close();
        /*if (remove(webfname.c_str()) != 0)
            perror("Error deleting file");
        else
            puts("File successfully deleted");*/
    }








    engrave << "Tag Number," << "Daily Number," << "SKU," << "Pet's Name," << "Line 1," << "Line 2," << "Line 3," << "Line 4" << "\n";

    unsigned int ind = 1;
    for (unsigned int i = 0; i < datavec.size(); i++) {
        for (unsigned int j = 0; j < datavec.at(i).size(); j++) {
            engrave << ind << ",";
            for (unsigned int k = 0; k < datavec[i][j].size(); k++) {
                std::string str2(datavec[i][j][k].size(), '0');
                str2.erase(std::remove_copy(datavec[i][j][k].begin(), datavec[i][j][k].end(), str2.begin(), ','), str2.end());
                engrave << str2 << ",";
            }
            engrave << "\n";
            ind++;
        }
    }


    automate << "inputbox, color, Enter Desired Colors #, Black being 3 blue being 6 orange being 1 grey being 2 white being 4 pink being 5"<< "\n";
    automate << "if ErrorLevel" << "\n";
    automate << "\t" << "color = 3" << "\n";

    automate << "^q::" << "\n";
    automate << "Sleep, 100" << "\n";
    automate << "MsgBox, Check your hatch settings" << "\n";

    /* Color Change*/
    automate << "if(color = 3 and inc = 1)" << "\n";
    automate << "\t" << "MsgBox, Engraving Black Please Change the Setting to..." << "\n";
    automate << "if(color = 1 and inc > " << orange << ")" << "\n";
    automate << "{" << "\n";
    automate << "\t" << "MsgBox, Engraving Grey Please Change the Setting to..." << "\n";
    automate << "\t" << "color := 2" << "\n";
    automate << "\t" << "inc := 1" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";
    automate << "if(color = 2 and inc > " << grey << ")" << "\n";
    automate << "{" << "\n";
    automate << "\t" << "MsgBox, Engraving White Please Change the Setting to..." << "\n";
    automate << "\t" << "color := 4" << "\n";
    automate << "\t" << "inc := 1" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";
    automate << "if(color = 3 and inc > " << black << ")" << "\n";
    automate << "{" << "\n";
    automate << "\t" << "MsgBox, Engraving Blue Please Change the Setting to..." << "\n";
    automate << "\t" << "color := 6" << "\n";
    automate << "\t" << "inc := 1" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";
    automate << "if(color = 4 and inc > " << white << ")" << "\n";
    automate << "{" << "\n";
    automate << "\t" << "MsgBox, Engraving Pink Please Change the Setting to..." << "\n";
    automate << "\t" << "color := 5" << "\n";
    automate << "\t" << "inc := 1" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";
    automate << "if(color = 5 and inc > " << pink << ")" << "\n";
    automate << "{" << "\n";
    automate << "\t" << "MsgBox, Engraving Orange Basic Tags" << "\n";
    automate << "\t" << "return" << "\n";
    automate << "}" << "\n";
    automate << "if(color = 6 and inc > " << blue << ")" << "\n";
    automate << "{" << "\n";
    automate << "\t" << "MsgBox, Engraving Orange please change the Setting to..." << "\n";
    automate << "\t" << "color := 1" << "\n";
    automate << "\t" << "inc := 1" << "\n";
    automate << "if(color = 7 and inc > " << orangeBasic << ")" << "\n";
    automate << "{" << "\n";
    automate << "\t" << "MsgBox, Done Engraving..." << "\n";
    automate << "\t" << "return" << "\n";
    automate << "}" << "\n";



/* Go To Next Size For Color */
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";
    automate << "if(color = 1 and size = 1 and sizeinc = " << variations[0] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=2" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 2 and sizeinc = " << variations[1] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=3" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 3 and sizeinc = " << variations[2] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=4" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 4 and sizeinc = " << variations[3] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=5" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 5 and sizeinc = " << variations[4] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=6" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 6 and sizeinc = " << variations[5] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "\tMsgBox, No more orange tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";




    automate << "if(color = 2 and size = 1 and sizeinc = " << variations[6] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=2" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 2 and sizeinc = " << variations[7] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=3" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 3 and sizeinc = " << variations[8] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=4" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 4 and sizeinc = " << variations[9] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=5" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 5 and sizeinc = " << variations[10] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=6" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 6 and sizeinc = " << variations[11] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "\tMsgBox, No more grey tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";




    automate << "if(color = 3 and size = 1 and sizeinc = " << variations[12] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=2" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 2 and sizeinc = " << variations[13] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=3" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 3 and sizeinc = " << variations[14] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=4" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 4 and sizeinc = " << variations[15] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=5" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 5 and sizeinc = " << variations[16] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=6" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 6 and sizeinc = " << variations[17] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "\tMsgBox, No more black tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";



    automate << "if(color = 4 and size = 1 and sizeinc = " << variations[18] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=2" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 2 and sizeinc = " << variations[19] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=3" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 3 and sizeinc = " << variations[20] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=4" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 4 and sizeinc = " << variations[21] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=5" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 5 and sizeinc = " << variations[22] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=6" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 6 and sizeinc = " << variations[23] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "\tMsgBox, No more white tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";



    automate << "if(color = 5 and size = 1 and sizeinc = " << variations[24] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=2" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 2 and sizeinc = " << variations[25] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=3" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 3 and sizeinc = " << variations[26] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=4" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 4 and sizeinc = " << variations[27] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=5" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 5 and sizeinc = " << variations[28] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=6" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 6 and sizeinc = " << variations[29] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "\tMsgBox, No more pink tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 1 and sizeinc = " << variations[30] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=2" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 2 and sizeinc = " << variations[31] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=3" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 3 and sizeinc = " << variations[32] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=4" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 4 and sizeinc = " << variations[33] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=5" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 5 and sizeinc = " << variations[34] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=6" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 6 and sizeinc = " << variations[35] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "\tMsgBox, No more blue tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 1 and sizeinc = " << variations[36] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=2" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 2 and sizeinc = " << variations[37] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=3" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 3 and sizeinc = " << variations[38] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=4" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 4 and sizeinc = " << variations[39] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=5" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 5 and sizeinc = " << variations[40] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=6" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 6 and sizeinc = " << variations[41] << ")\n";
    automate << "{" << "\n";
    automate << "\tsize:=1" << "\n";
    automate << "\tsizeinc:=1" << "\n";
    automate << "\tMsgBox, No more Orange Basic tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

/* Load DXF Files Into Workspace */
    automate << "Send, ^b" << "\n";
    automate << "Sleep, 400" << "\n";

    automate << "if(color = 1 and size = 1 and sizeinc < " << variations[0] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, O%sizeinc%XS.dxf" << "\n";
    automate << "\tTarget := \"XS\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 2 and sizeinc < " << variations[1] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, O%sizeinc%S.dxf" << "\n";
    automate << "\tTarget := \"S\"" << "\n";;
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 3 and sizeinc < " << variations[2] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, O%sizeinc%M.dxf" << "\n";
    automate << "\tTarget := \"M\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 4 and sizeinc < " << variations[3] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, O%sizeinc%ML.dxf" << "\n";
    automate << "\tTarget := \"ML\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 5 and sizeinc < " << variations[4] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, O%sizeinc%L.dxf" << "\n";
    automate << "\tTarget := \"L\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 1 and size = 6 and sizeinc < " << variations[5] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, O%sizeinc%XL.dxf" << "\n";
    automate << "\tTarget := \"XL\"" << "\n";
    automate << "}" << "\n";


    automate << "if(color = 2 and size = 1 and sizeinc < " << variations[6] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, G%sizeinc%XS.dxf" << "\n";
    automate << "\tTarget := \"XS\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 2 and sizeinc < " << variations[7] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, G%sizeinc%S.dxf" << "\n";
    automate << "\tTarget := \"S\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 3 and sizeinc < " << variations[8] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, G%sizeinc%M.dxf" << "\n";
    automate << "\tTarget := \"M\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 4 and sizeinc < " << variations[9] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, G%sizeinc%ML.dxf" << "\n";
    automate << "\tTarget := \"ML\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 5 and sizeinc < " << variations[10] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, G%sizeinc%L.dxf" << "\n";
    automate << "\tTarget := \"L\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 2 and size = 6 and sizeinc < " << variations[11] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, G%sizeinc%XL.dxf" << "\n";
    automate << "\tTarget := \"XL\"" << "\n";
    automate << "}" << "\n";


    automate << "if(color = 3 and size = 1 and sizeinc < " << variations[12] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BK%sizeinc%XS.dxf" << "\n";
    automate << "\tTarget := \"XS\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 2 and sizeinc < " << variations[13] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BK%sizeinc%S.dxf" << "\n";
    automate << "\tTarget := \"S\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 3 and sizeinc < " << variations[14] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BK%sizeinc%M.dxf" << "\n";
    automate << "\tTarget := \"M\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 4 and sizeinc < " << variations[15] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BK%sizeinc%ML.dxf" << "\n";
    automate << "\tTarget := \"ML\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 5 and sizeinc < " << variations[16] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BK%sizeinc%L.dxf" << "\n";
    automate << "\tTarget := \"L\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 3 and size = 6 and sizeinc < " << variations[17] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BK%sizeinc%XL.dxf" << "\n";
    automate << "\tTarget := \"XL\"" << "\n";
    automate << "}" << "\n";


    automate << "if(color = 4 and size = 1 and sizeinc < " << variations[18] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, W%sizeinc%XS.dxf" << "\n";
    automate << "\tTarget := \"XS\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 2 and sizeinc < " << variations[19] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, W%sizeinc%S.dxf" << "\n";
    automate << "\tTarget := \"S\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 3 and sizeinc < " << variations[20] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, W%sizeinc%M.dxf" << "\n";
    automate << "\tTarget := \"M\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 4 and sizeinc < " << variations[21] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, W%sizeinc%ML.dxf" << "\n";
    automate << "\tTarget := \"ML\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 5 and sizeinc < " << variations[22] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, W%sizeinc%L.dxf" << "\n";
    automate << "\tTarget := \"L\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 4 and size = 6 and sizeinc < " << variations[23] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, W%sizeinc%XL.dxf" << "\n";
    automate << "\tTarget := \"XL\"" << "\n";
    automate << "}" << "\n";


    automate << "if(color = 5 and size = 1 and sizeinc < " << variations[24] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, P%sizeinc%XS.dxf" << "\n";
    automate << "\tTarget := \"XS\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 2 and sizeinc < " << variations[25] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, P%sizeinc%S.dxf" << "\n";
    automate << "\tTarget := \"S\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 3 and sizeinc < " << variations[26] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, P%sizeinc%M.dxf" << "\n";
    automate << "\tTarget := \"M\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 4 and sizeinc < " << variations[27] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, P%sizeinc%ML.dxf" << "\n";
    automate << "\tTarget := \"ML\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 5 and sizeinc < " << variations[28] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, P%sizeinc%L.dxf" << "\n";
    automate << "\tTarget := \"L\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 5 and size = 6 and sizeinc < " << variations[29] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, P%sizeinc%XL.dxf" << "\n";
    automate << "\tTarget := \"XL\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 1 and sizeinc < " << variations[30] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BL%sizeinc%XS.dxf" << "\n";
    automate << "\tTarget := \"XS\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 2 and sizeinc < " << variations[31] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BL%sizeinc%S.dxf" << "\n";
    automate << "\tTarget := \"S\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 3 and sizeinc < " << variations[32] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BL%sizeinc%M.dxf" << "\n";
    automate << "\tTarget := \"M\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 4 and sizeinc < " << variations[33] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BL%sizeinc%ML.dxf" << "\n";
    automate << "\tTarget := \"ML\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 5 and sizeinc < " << variations[34] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BL%sizeinc%L.dxf" << "\n";
    automate << "\tTarget := \"L\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 6 and size = 6 and sizeinc < " << variations[35] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, BL%sizeinc%XL.dxf" << "\n";
    automate << "\tTarget := \"XL\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 1 and sizeinc < " << variations[36] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, OB%sizeinc%XS.dxf" << "\n";
    automate << "\tTarget := \"XS\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 2 and sizeinc < " << variations[37] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, OB%sizeinc%S.dxf" << "\n";
    automate << "\tTarget := \"S\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 3 and sizeinc < " << variations[38] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, OB%sizeinc%M.dxf" << "\n";
    automate << "\tTarget := \"M\"" << "\n";
    automate << "}" << "\n";

    automate << "if(color = 7 and size = 4 and sizeinc < " << variations[39] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, OB%sizeinc%ML.dxf" << "\n";
    automate << "\tTarget := \"ML\"" << "\n";
    automate << "}" << "\n";
    
    automate << "if(color = 7 and size = 5 and sizeinc < " << variations[40] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, OB%sizeinc%L.dxf" << "\n";
    automate << "\tTarget := \"L\"" << "\n";
    automate << "}" << "\n";
    
    automate << "if(color = 7 and size = 6 and sizeinc < " << variations[41] << ")\n";
    automate << "{" << "\n";
    automate << "\t" << "Send, OB%sizeinc%XL.dxf" << "\n";
    automate << "\tTarget := \"XL\"" << "\n";
    automate << "}" << "\n";

/* Hatch and Position DXF Files */

    automate << "Send, {Enter}" << "\n";
    automate << "Sleep, 100" << "\n";
    automate << "Send, ^h" << "\n";
    automate << "Sleep, 100" << "\n";
    automate << "Send, {Enter}" << "\n";

    automate << "%Target%()" << "\n";
    automate << "diff := curpos-dist" << "\n";
    automate << "if(diff > -3.35)" << "\n";
    automate << "{" << "\n";
    automate << "\ttagpos := dist/2" << "\n";
    automate << "\tif(curpos > tagpos)" << "\n";
    automate << "\t{" << "\n";
    automate << "\t\tdiff1 := tagpos+bignudge" << "\n";
    automate << "\t\twhile(diff1 < curpos)" << "\n";
    automate << "\t\t{" << "\n";
    automate << "\t\t\tSend, +{Up}" << "\n";
    automate << "\t\t\ttagpos:=tagpos+bignudge" << "\n";
    automate << "\t\t\tdiff1 := tagpos+bignudge" << "\n";
    automate << "\t\t}" << "\n";
    automate << "\t\tcurpos:=tagpos-dist-spacing" << "\n";
    automate << "\t}" << "\n";
    automate << "\telse" << "\n";
    automate << "\t{" << "\n";

    automate << "\t\twhile(tagpos > curpos)" << "\n";
    automate << "\t\t{" << "\n";
    automate << "\t\t\tSend, +{Down}" << "\n";
    automate << "\t\t\ttagpos:=tagpos-bignudge" << "\n";
    automate << "\t\t}" << "\n";
    automate << "\t\tcurpos:=tagpos-dist-spacing" << "\n";
    automate << "\t}" << "\n";
    automate << "}" << "\n";

/* Go To Next Color*/

    automate << "if(inc = " << orange << " and color = 1)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, No more orange tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(inc = " << grey << " and color = 2)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, No more grey tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(inc = " << black << " and color = 3)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, No more black tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(inc = " << white << " and color = 4)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, No more white tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(inc = " << pink << " and color = 5)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, No more pink tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(inc = " << blue << " and color = 6)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, No more blue tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

    automate << "if(inc = " << orangeBasic << " and color = 7)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, No more Orange Basic tags ready to engrave" << "\n";
    automate << "\tcurpos:=3.35" << "\n";
    automate << "}" << "\n";

/* Supporting Functions For Placement*/

    automate << "inc := inc + 1" << "\n";
    automate << "sizeinc := sizeinc + 1" << "\n";

    automate << "if(size = 1)" << "\n";
    automate << "\tNext := \"XS\"\n";
    automate << "if(size = 2)" << "\n";
    automate << "\tNext := \"S\"\n";
    automate << "if(size = 3)" << "\n";
    automate << "\tNext := \"M\"\n";
    automate << "if(size = 4)" << "\n";
    automate << "\tNext := \"ML\"\n";
    automate << "if(size = 5)" << "\n";
    automate << "\tNext := \"L\"\n";
    automate << "if(size = 6)" << "\n";
    automate << "\tNext := \"XL\"\n";


    automate << "%Next%()" << "\n";
    automate << "dif := curpos-dist" << "\n";
    automate << "if(dif < -3.35)" << "\n";
    automate << "{" << "\n";
    automate << "\tMsgBox, Can't fit anymore tags ready to engrave" << "\n";
    automate << "\tcurpos := 3.334" << "\n";
    automate << "}" << "\n";
    automate << "return" << "\n";

/* Debug Mode */

    automate << "^l::\n";
    automate << "msgbox, TagNo: %inc% Color: %color% Size: %size% SizeNo: %sizeinc%" << "\n";
    automate << "return" << "\n";



    cout << "done\n";


}



void produce_tag(string order_id, string asin, string sku, string pet_name, string line1, string line2, string line3, string line4, bool line1found
    , bool line2found, bool line3found, bool line4found, int lines_found, int start_index, bool website, bool quantity) {

top:

    bool line1hang = false;
    bool line2hang = false;
    bool line3hang = false;
    bool line4hang = false;
    bool namehang = false;
    string flag = " ";
/* Checking For Forbidden Phrases*/

    vector<string> forbidden = { "Grand", "1", "2", "Returning", "Line" };

    for (unsigned int i = 0; i < forbidden.size(); i++) {

        if (line1 == forbidden[i]) {
            line1found = false;
        }
        if (line2 == forbidden[i]) {
            line2found = false;
        }
        if (line3 == forbidden[i]) {
            line3found = false;
        }
        if (line4 == forbidden[i]) {
            line4found = false;
        }
    }

    for (unsigned int i = 0; i < sizeof(hang) / sizeof(hang[0]); i++) {
        if (line1.find(hang[i]) != std::string::npos)
        {
            line1hang = true;
        }
        if (line2.find(hang[i]) != std::string::npos)
        {
            line2hang = true;
        }
        if (line3.find(hang[i]) != std::string::npos)
        {
            line3hang = true;
        }
        if (line4.find(hang[i]) != std::string::npos)
        {
            line4hang = true;
        }
        if (pet_name.find(hang[i]) != std::string::npos)
        {
            namehang = true;
        }
    }

    if (lines_found == 3 && !(line1found && line2found && line3found)) {
        if (!line1found) {
            line1 = line2;
            line2 = line3;
            line3 = line4;
            line1hang = line2hang;
            line2hang = line3hang;
            line3hang = line4hang;
        }
        if (!line2found) {
            line2 = line3;
            line3 = line4;
            line2hang = line3hang;
            line3hang = line4hang;
        }
        if (!line3found) {
            line3 = line4;
            line3hang = line4hang;
        }
        line4 = " ";
    }

    if (lines_found == 2 && !(line1found && line2found)) {
        if (line1found && line3found) {
            line2 = line3;
            line2hang = line3hang;
        }
        if (line1found && line4found) {
            line2 = line4;
            line2hang = line4hang;
        }
        if (line2found && line3found) {
            line1 = line2;
            line2 = line3;
            line1hang = line2hang;
            line2hang = line3hang;
        }
        if (line2found && line4found) {
            line1 = line2;
            line2 = line4;
            line1hang = line2hang;
            line2hang = line4hang;
        }
        if (line3found && line4found) {
            line1 = line3;
            line2 = line4;
            line1hang = line3hang;
            line2hang = line4hang;
        }
        line3 = " ";
        line4 = " ";
    }
    if (lines_found == 1 && !(line1found)) {

        if (line2found) {
            line1 = line2;
            line1hang = line2hang;
        }
        if (line3found) {
            line1 = line3;
            line1hang = line3hang;
        }
        if (line4found) {
            line1 = line4;
            line1hang = line4hang;
        }
        line2 = " ";
        line3 = " ";
        line4 = " ";
    }


    char start_char;
    if (website) {
        start_char = 'W';
    }
    else {
        start_char = 'A';
    }

/* Engrave.csv File Creation */

    csvfile << "Order ID: # " << order_id << "\n";
    csvfile << start_char << start_index << "\n\n\n";
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





    int size = 0;
    int color_num = 0;
    int variation_num;

    /* Color Split */

    if (split(sku,"-")[0]  == "O") {
        orange++;
        color = "O";
        number = orange;
        color_num = 0;
    }else if (split(sku,"-")[0]  == "W") {
        white++;
        color = "W";
        number = white;
        color_num = 18;

    }else if (split(sku,"-")[0]  == "BK") {
        black++;
        color = "BK";
        number = black;
        color_num = 12;
    }else if (split(sku,"-")[0]  == "G") {
        grey++;
        color = "G";
        number = grey;
        color_num = 6;
    }else if (split(sku,"-")[0]  == "P") {
        pink++;
        color = "P";
        number = pink;
        color_num = 24;
    }else if (split(sku,"-")[0]  == "BL") {
        blue++;
        color = "BL";
        number = blue;
        color_num = 30;
    }else if (split(sku,"-")[0]  == "OB") {
        orangeBasic++;
        color = "OB";
        number = orangeBasic;
        color_num = 36;
    }else {
        return;
    }

    int x = 0;

/* Size Split */

    if (split(sku,"-")[1]  == "XS") {
        size = 0;
        x = 20;
    }else if (split(sku,"-")[1]  == "S") {
        size = 1;
        x = 16;
    }else if (split(sku,"-")[1]  == "M") {
        size = 2;
        x = 12;
    }else if (split(sku,"-")[1]  == "ML") {
        size = 3;
        x = 8;
    }else if (split(sku,"-")[1]  == "L") {
        size = 4;
        x = 4;
    }else if (split(sku,"-")[1]  == "XL") {
        size = 5;
        x = 0;
    }else {
        return;
    }

    variation_num = color_num + size;

    variations.at(variation_num)++;



    if (lines_found == 3) {
        x++;
    }
    if (lines_found == 2) {
        x = x + 2;
    }
    if (lines_found == 1) {
        x = x + 3;
    }

    std::transform(pet_name.begin(), pet_name.end(), pet_name.begin(),
        [](unsigned char c) { return std::toupper(c); });
    std::transform(line1.begin(), line1.end(), line1.begin(),
        [](unsigned char c) { return std::toupper(c); });
    std::transform(line2.begin(), line2.end(), line2.begin(),
        [](unsigned char c) { return std::toupper(c); });
    std::transform(line3.begin(), line3.end(), line3.begin(),
        [](unsigned char c) { return std::toupper(c); });
    std::transform(line4.begin(), line4.end(), line4.begin(),
        [](unsigned char c) { return std::toupper(c); });




    script << ";" << start_char << start_index << "\n";
    script << ";Order ID: # " << order_id << "\n";

    float pos;
    std::string line;
    std::string linex;
    float height_scaler = 0.25;

    if (pet_name != " ") {
        if (namehang) {
            line = parsedCsv[1][x];
            linex = line.substr(line.find(",") + 1);
            linex = linex.substr(linex.find(",") + 1);
            pos = stof(linex);


            std::string toReplace(linex);
            size_t posit = line.find(toReplace);

            while (line.back() != ',')
                line.pop_back();
            pos = pos + stof(heights[2][x + 1]) * height_scaler;
            line = line + to_string(pos);
            line.replace(posit, toReplace.length(), to_string(pos));
            script << line;

            script << " " << heights[2][x + 1] << " ";
        }
        else {
            script << parsedCsv[1][x];
            script << " " << heights[1][x + 1] << " ";
        }
    }
    else {
        script << parsedCsv[1][x];
    }
    script << pet_name << "\n";



    if (line1 != " ") {

        if (line1hang) {
            line = parsedCsv[2][x];
            linex = line.substr(line.find(",") + 1);
            linex = linex.substr(linex.find(",") + 1);
            pos = stof(linex);


            std::string toReplace(linex);
            size_t posit = line.find(toReplace);

            while (line.back() != ',')
                line.pop_back();
            pos = pos + stof(heights[4][x + 1]) * height_scaler;
            line = line + to_string(pos);
            line.replace(posit, toReplace.length(), to_string(pos));
            script << line;




            script << " " << heights[4][x + 1] << " ";
        }
        else {
            script << parsedCsv[2][x];
            script << " " << heights[3][x + 1] << " ";
        }
    }
    else {
        script << parsedCsv[2][x];
    }
    script << line1 << "\n";

    if (line2 != " ") {
        if (line2hang) {
            line = parsedCsv[3][x];
            linex = line.substr(line.find(",") + 1);
            linex = linex.substr(linex.find(",") + 1);
            pos = stof(linex);


            std::string toReplace(linex);
            size_t posit = line.find(toReplace);

            while (line.back() != ',')
                line.pop_back();
            pos = pos + stof(heights[4][x + 1]) * height_scaler;
            line = line + to_string(pos);
            line.replace(posit, toReplace.length(), to_string(pos));
            script << line;
            script << " " << heights[4][x + 1] << " ";
        }
        else {
            script << parsedCsv[3][x];
            script << " " << heights[3][x + 1] << " ";
        }

    }
    else {
        script << parsedCsv[3][x];
    }
    script << line2 << "\n";

    if (line3 != " ") {
        if (line3hang) {
            line = parsedCsv[4][x];
            linex = line.substr(line.find(",") + 1);
            linex = linex.substr(linex.find(",") + 1);
            pos = stof(linex);


            std::string toReplace(linex);
            size_t posit = line.find(toReplace);

            while (line.back() != ',')
                line.pop_back();
            pos = pos + stof(heights[4][x + 1]) * height_scaler;
            line = line + to_string(pos);
            line.replace(posit, toReplace.length(), to_string(pos));
            script << line;
            script << " " << heights[4][x + 1] << " ";
        }
        else {
            script << parsedCsv[4][x];
            script << " " << heights[3][x + 1] << " ";
        }
    }
    else {
        script << parsedCsv[4][x];
    }
    script << line3 << "\n";

    if (line4 != " ") {
        if (line4hang) {
            line = parsedCsv[5][x];
            linex = line.substr(line.find(",") + 1);
            linex = linex.substr(linex.find(",") + 1);
            pos = stof(linex);


            std::string toReplace(linex);
            size_t posit = line.find(toReplace);

            while (line.back() != ',')
                line.pop_back();
            pos = pos + stof(heights[4][x + 1]) * height_scaler;
            line = line + to_string(pos);
            line.replace(posit, toReplace.length(), to_string(pos));
            script << line;
            script << " " << heights[4][x + 1] << " ";
        }
        else {
            script << parsedCsv[5][x];
            script << " " << heights[3][x + 1] << " ";
        }
    }
    else {
        script << parsedCsv[5][x];
    }
    script << line4 << "\n";

/* Copy Save And Delete DXF */

    script << parsedCsv[6][x] << "\n";
    script << parsedCsv[7][x] << "\n";
    script << parsedCsv[8][x] << "\n";
    script << parsedCsv[9][x] << "\n";
    script << parsedCsv[10][x] << "\n";
    script << parsedCsv[11][x] << "\n";
    script << parsedCsv[12][x] << "\n";
    script << parsedCsv[13][x] << "\n";
    script << parsedCsv[14][x] << "\n";
    script << parsedCsv[15][x] << "\n";
    script << parsedCsv[16][x] << "\n";
    script << parsedCsv[17][x] << "\n";
    script << parsedCsv[18][x] << "\n";
    script << parsedCsv[19][x] << "\n";
    script << parsedCsv[20][x] << "\n";
    script << parsedCsv[21][x] << month <<"\\" << mon << "-" << to_string(timeinfo->tm_mday) << "\\" << color << variations[variation_num] - 1 << sizes[size] << ".dxf\n";
    script << parsedCsv[22][x] << "\n\n";


    std::vector<string> toInsert;
    //toInsert.push_back(to_string(start_index));
    toInsert.push_back(color + to_string(variations[variation_num] - 1) + sizes[size]);
    toInsert.push_back(sku);
    toInsert.push_back(pet_name);
    toInsert.push_back(line1);
    toInsert.push_back(line2);
    toInsert.push_back(line3);
    toInsert.push_back(line4);
    toInsert.push_back(flag);

    datavec.at(variation_num).push_back(toInsert);
if (quantity) {
    quantity = false;
    goto top;
}

}