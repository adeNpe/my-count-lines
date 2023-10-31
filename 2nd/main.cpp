#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <io.h>
#include <Windows.h>
#include <cstdio>
#include <iomanip>

using namespace std;

/*------类------*/
class Code {

public:
    int errorNum = 0;
    int genreC = 0;
    int genreJAVA = 0;
    int genrePYTHON = 0;
    int genreHTML = 0;
    int genreUNKNOW = 0;
    int getTotalCodeLineNum() {
        return genreC+genreUNKNOW+genreHTML+genrePYTHON+genreJAVA;
    }

private:
    struct C {
        int c_code_num = 0;
        int c_function_num = 0;
        int c_function_code_num = 0;
        int c_function_code_num_max = 0;
        int c_function_code_num_min = 0;
        int c_function_code_num_average = 0;
    }c;
    struct JAVA {
        int java_code_num = 0;
        int java_function_num = 0;
        int java_function_code_num = 0;
        int java_function_code_num_max = 0;
        int java_function_code_num_min = 0;
        int java_function_code_num_average = 0;
    }java;

} myCode;//记录目标代码的数据的类实例
class TestTool {
public:
    string dataSource = "D:/test/testSource";//所要统计的目标文件夹
    string relativePath_of_OutputHTML = "\\chartOutput\\chartOutput.html";//HTML文件的相对路径
    char *pathInfo = "D:/test/testTool/chartOutput/AllFiles.txt";//递归目标文件夹得来的、记录所有子文件夹和文件路径的信息
    char *copyTemp = "D:/test/testTool/temp";//把所有代码文件另存为txt格式所用的临时文件夹，内容物用后即删
    char *temp = "D:/test/testTool/chartOutput/temp.txt";//逐行识别代码的临时文件、把所有代码按字符串格式弄到txt里再逐行读，用后即删
    char *outputHTML = "D:/test/testTool/chartOutput/chartOutput.html";//呈现结果的HTML位置
    char *outputCSS = "D:/test/testTool/chartOutput/chartInfoInputScript.css";//负责结果呈现网页上那个图怎么画的数据
    char *outputJS = "D:/test/testTool/chartOutput/chartInfo.js";//统计结束后保存图形化界面里文字数据的JS位置
    void initializeProgramPackageDefaultSetting()//这个函数是用来将测试时所用的绝对路径改成构建后exe文件所使用的相对路径的
    {
        pathInfo = "./chartOutput/AllFiles.txt";
        temp = "./chartOutput/temp.txt";
        //outputHTML = "./chartOutput/chartOutput.html"; //因为这个是cmd命令，相对路径固定为clion编译时工程的位置，所以无效
        outputCSS = "./chartOutput/chartInfoInputScript.css";
        outputJS = "./chartOutput/chartInfo.js";
    }
    void setDataSource(){

    }
    TestTool() {
        char buffer[MAX_PATH];//用于存放获取的路径信息。
        GetModuleFileName(NULL, buffer, MAX_PATH);
        string parentFolderPath = buffer;
        int pos = parentFolderPath.rfind('\\');//查找路径里最后一个“\”符号位置
        parentFolderPath = parentFolderPath.erase(pos, parentFolderPath.length() - pos);
        parentFolderPath += relativePath_of_OutputHTML;//这样无论这个exe拷贝到哪它都能定位到同文件夹下的子文件夹chartOutput下的哪个HTML了
        //this->initializeProgramPackageDefaultSetting();
        //strcpy(this->outputHTML, parentFolderPath.c_str());
        /* ---注意---
         * 上述两行之所以注释掉，
         * 是因为在开发阶段本项目在cmake里生成的可执行文件和其配套的前端文件是分隔开的，
         * 实际使用时是将这个cmake-build-debug里的exe拷贝到testTool里执行的，
         * 所以路径也是需要修改的。
         * */
    }
} myTestTool;//用以协调此工程相关文件路径的确定

/*------函数声明------*/
void setDataSourcePath();//启动程序时的一个交互界面，用以设置用户目标文件夹dataSource、前端文件、统计时临时文件的路径
void getAllFilesFunction(const string &, vector<string> &files);//getAllFiles函数的递归工具
void getAllFiles(TestTool &myTestTool);//记录所有子文件夹和文件路径的信息
void coreCode(Code &report, TestTool &myTestTool);//遍历所有代码的核心代码
void dosOutput(Code &report);//dos窗口非图形化结果的呈现
void editWebDisplayAttributeSetting(Code &report, TestTool &myTestTool);//web端呈现的图形化结果的数据传入

/*------函数------*/
void setDataSourcePath() {

} //打开QT
void getAllFilesFunction(const string &path, vector<string> &files) {
    //文件句柄
    intptr_t hFile = 0;
    //文件信息
    struct _finddata_t fileinfo; //很少用的文件信息读取结构
    string p; //string类很有意思的一个赋值函数:assign()，有很多重载版本
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) //判断是否为文件夹
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("/").append(fileinfo.name));//保存文件夹名字
                    getAllFilesFunction(p.assign(path).append("/").append(fileinfo.name), files);//递归当前文件夹
                }
            } else  //文件处理
            {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));//文件名
            }
        } while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }
}
void getAllFiles(TestTool &myTestTool) {
    vector<string> files;
    getAllFilesFunction(myTestTool.dataSource, files);//所有文件与文件夹的路径都输出
    ofstream ofn(myTestTool.pathInfo); //输出文件流
    int size = files.size();
    ofn << size << endl;
    for (int i = 0; i < size; i++) {
        ofn << files[i] << endl;
    }
    ofn.close();
}
void coreCode(Code &report, TestTool &myTestTool)
{
    ifstream fin;
    fin.open(myTestTool.pathInfo, ios::in);
    char target[MAX_PATH], buffer[MAX_PATH] = {0};
    strcpy(target,myTestTool.copyTemp);
    int START_POINT = strlen(target);
    while (fin.getline(buffer, sizeof(buffer))) {
        int backslashPosition = 0;
        int dotPosition = 0;
        for (int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '/')
                backslashPosition = i;
            if (buffer[i] == '.')
                dotPosition = i;
        }

        if (dotPosition == 0 || backslashPosition > dotPosition)
            /* backslashPosition > dotPosition可以在*一定程度*上防止路径中含有点导致的识别错误，
             * 例如「D:/test/testSource/VC80Samples/VC++ 8.0 Samples/ATL/Advanced/ActiveDoc/ActiveCtl.cpp」的、
             * 那个「VC++ 8.0」的点对文件后缀名识别的影响*/
        {
            strcpy(buffer, "");
            strcpy(target,myTestTool.copyTemp);
            continue; //识别到文件数目或者文件夹路径
        }

        int dotPositionTarget;
        for (int i = backslashPosition, j = START_POINT; i < dotPosition; i++, j++) {
            target[j] = buffer[i];
            dotPositionTarget = j;
        }

        target[dotPositionTarget + 1] = '.';
        target[dotPositionTarget + 2] = 't';
        target[dotPositionTarget + 3] = 'x';
        target[dotPositionTarget + 4] = 't';
        target[dotPositionTarget + 5] = '\0';
        //完成修改后的txt路径

        if (!CopyFile(buffer, target, FALSE)) {
            report.errorNum++;
        }
        else {
            SetFileAttributes(target, FILE_ATTRIBUTE_NORMAL);
            ifstream fin2;
            fin2.open(target, ios::in);
            char codeBuffer[102400] = {0};
            int type;
            if ((buffer[dotPosition + 1] == 'c' && buffer[dotPosition + 2] == 'p' && buffer[dotPosition + 3] == 'p') //.cpp
                || (buffer[dotPosition + 1] == 'c' && buffer[dotPosition + 2] == '\0') //.c
                || (buffer[dotPosition + 1] == 'h' && buffer[dotPosition + 2] == '\0') //.h
                || (buffer[dotPosition + 1] == 'C' && buffer[dotPosition + 2] == '\0')) //.C
                type=0;
            else if (buffer[dotPosition + 1] == 'j' && buffer[dotPosition + 2] == 'a' &&
                     buffer[dotPosition + 3] == 'v' && buffer[dotPosition + 4] == 'a') //.java
                type=1;
            else if (buffer[dotPosition + 1] == 'p' && buffer[dotPosition + 2] == 'y') //.py
                type=2;
            else if (buffer[dotPosition + 1] == 'h' && buffer[dotPosition + 2] == 't' &&
                     buffer[dotPosition + 3] == 'm') //.htm & .html
                type=3;
            else
                type=4;
            while (fin2.getline(codeBuffer, sizeof(codeBuffer))) {
                switch(type)
                {
                    case 0: report.genreC++; break;
                    case 1: report.genreJAVA++; break;
                    case 2: report.genrePYTHON++; break;
                    case 3: report.genreHTML++; break;
                    case 4: report.genreUNKNOW++; break;
                }
            }
            fin2.close();
            if (!DeleteFile(target))
                cout << endl << "Failed to delete temp" << endl;
        }

        for (int i = 0; i < sizeof(buffer); i++) {
            buffer[i] = '\0';
        }

        for (int i = START_POINT; i < sizeof(target); i++) {
            target[i] = '\0';
        }
    }
}
void dosOutput(Code &report) {
    cout << "The total number of code lines is " << report.getTotalCodeLineNum() << endl;
    cout << "C/CPP: " << report.genreC << endl;
    cout << "Java: " << report.genreJAVA << endl;
    cout << "Python: " << report.genrePYTHON << endl;
    cout << "HTML/HTM: " << report.genreHTML << endl;
    cout << "unrecognized/uncounted format: " << report.genreUNKNOW << endl;
    cout << "error number: " << report.errorNum << endl;
    cout
            << "(for instance, error often occurs when there exists a dot(ascii 46D) in the filename path but not represents for the\nsuffix name of the format)"
            << endl;
}
void editWebDisplayAttributeSetting(Code &report, TestTool &myTestTool) {
    auto all = (float) report.getTotalCodeLineNum();
    auto c = (float) report.genreC * 100 / all;
    auto java = (float) report.genreJAVA * 100 / all;
    auto python = (float) report.genrePYTHON * 100 / all;
    auto html = (float) report.genreHTML * 100 / all;
    auto unrecognized = (float) report.genreUNKNOW * 100 / all;
    int start = 500;

    ofstream ofs;
    ofs.open(myTestTool.temp, ios::out);
    ofs
            << "#C{width:" << c * 15 << "px;margin:0 0 0 " << start << "px;}\n"
            << "#Java{width:" << java * 15 << "px;margin:0 0 0 " << c * 15 << "px;}\n"
            << "#Python{width:" << python * 15 << "px;margin:0 0 0 " << java * 15 << "px;}\n"
            << "#HTML{width:" << html * 15 << "px;margin:0 0 0 " << python * 15 << "px;}\n"
            << "#unrecognized{width:" << unrecognized * 15 << "px;margin:0 0 0 " << html * 15 << "px;}\n";
    ofs.close();
    if (!CopyFile(myTestTool.temp, myTestTool.outputCSS, FALSE))
        cout << "failed to create css";

    ofs.open(myTestTool.temp, ios::out);
    ofs
            << setiosflags(ios::fixed) << setprecision(2) //输出保留两位小数
            << "var c=" << report.genreC << ";\n"
            << "var java=" << report.genreJAVA << ";\n"
            << "var python=" << report.genrePYTHON << ";\n"
            << "var html=" << report.genreHTML << ";\n"
            << "var unrecognized=" << report.genreUNKNOW << ";\n"
            << "var cP=" << c << ";\n"
            << "var javaP=" << java << ";\n"
            << "var pythonP=" << python << ";\n"
            << "var htmlP=" << html << ";\n"
            << "var unP=" << unrecognized << ";\n"
            << "var codeAll=" << all << ";\n";
    ofs.close();
    if (!CopyFile(myTestTool.temp, myTestTool.outputJS, FALSE))
        cout << "failed to create css";
    if (!DeleteFile(myTestTool.temp))
        cout << endl << "Failed to delete temp" << endl;
}

/*------main()------*/
int main() {
    setDataSourcePath();
    cout<<"统计中，请稍后……";
    getAllFiles(myTestTool);
    coreCode(myCode, myTestTool);
    dosOutput(myCode); //dos窗口内结果显示
    editWebDisplayAttributeSetting(myCode, myTestTool);
    system(myTestTool.outputHTML); //前端，启动！
    system("pause");//以防打不开浏览器
    return 0;
}
