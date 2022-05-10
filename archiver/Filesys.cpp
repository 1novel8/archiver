#include"Filesys.h"


void dirwalk(boost::filesystem::directory_iterator path, std::vector<std::string>& paths) {
    boost::filesystem::directory_iterator end;
    for (; path != end; path++) {
        boost::filesystem::file_status fs = path->status();
        paths.push_back(path->path().string());
        if (fs.type() == boost::filesystem::directory_file) {
            boost::filesystem::directory_iterator dir(path->path());
            dirwalk(dir, paths);
        }
        std::cout << *path << '\n';
    }
}
void dirwalkLite(boost::filesystem::directory_iterator path, std::vector<std::string>& paths, bool show) {
    boost::filesystem::directory_iterator end;
    for (; path != end; path++) {
        boost::filesystem::file_status fs = path->status();
        std::string str = path->path().string();
        if (str[3] != '$' && !findWord(str, "System Volume Information")) {
            if(show)
                paths.push_back(path->path().string());
            else if(rightHFF(str)|| fs.type() == boost::filesystem::directory_file)
                paths.push_back(path->path().string());
        }
           
    }
}
bool findWord(std::string mainStr, std::string str) {
    for (int i = 0, j=0; i < mainStr.size(); i++) {
        if (mainStr[i] == str[j]) {
            j++;
            if (j == str.size() - 1)
                return true;
        }
        else
            j = 0;
    }
    return false;
}

bool isItFile(std::string path) {
    //path += '\\';
    //boost::filesystem::directory_iterator file(path);
    //boost::filesystem::file_status fs = file->status();
    if (boost::filesystem::is_regular_file(path)) {
        //path.pop_back();
        return true;
    }
    else return false;
    /*int i = 0;
    while (i< path.size()) {
        if (path[i] == '.')
            return true;
        i++;
    }
    return false;*/
}

std::string getName(std::string path) {
    int i = path.size()-1;
    while (path[i] != '\\' && path[i] != '/')
        i--;
    i++;
    std::string name;
    while (i <path.size()) {
        name += path[i];
        i++;
    }
    i = 0;
    while(i<name.size()){
        if (name[i] == '.') {
            i++;
            name[i] = 'h';
            name[i + 1] = 'f';
            name[i + 2] = 'f';
            name[i + 3] = '\0';
            return name;
        }
        i++;
    }
    name += ".hff";
    return name;

}

std::string getWorkPath(std::string pathIn, std::string curPath) {
    std::string workPath="";
    if (isItFile(pathIn)) {
        int i = pathIn.size() - 1;
        while (pathIn[i] != '\\' && pathIn[i] != '/')
            i--;
        i++;
        std::string workPath;
        while (i < pathIn.size()) {
            workPath += pathIn[i];
            i++;
        }
        return workPath;
    }
    int i = pathIn.size();
    while (pathIn[i] != '\\' && pathIn[i] != '/' && pathIn[i] != ':')
        i--;
    i++;
    for (; i < curPath.size(); i++) {
        workPath += curPath[i];
    }
    return workPath;
}

void writePaths(std::string pathIn,std:: string pathOut, std::vector<std::string>listOfFiles) {
    std::ofstream out(pathOut, std::ios_base::binary);
    if (!out) {
        std::cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
        return;
    }
    char f = 'f', d = 'd';
    int size = listOfFiles.size();
    out.write((char*)(&size), sizeof(int));
    for (int i = 0; i < listOfFiles.size(); i++) {
        std::string pth = getWorkPath(pathIn, listOfFiles[i]);
        int pathSize = pth.size()+1;
        out.write(reinterpret_cast<char*>(&pathSize), sizeof(int));
        for (int j = 0; j < pth.size(); j++) {
            out.write(&pth[j], sizeof(char));
        }
        if (isItFile(listOfFiles[i]))
            out.write(&f, sizeof(char));
        else
            out.write(&d, sizeof(char));
    }
}

std::ifstream::pos_type getPaths(std::string pathIn, std::vector<std::string>& listOfFiles, std::string pathOut) {
    std::ifstream in(pathIn, std::ios_base::binary);
    if (!in) {
        std::cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
        return 0;
    }
    int size;
    in.read((char*)(&size), sizeof(int));
    for (int i = 0; i < size; i++) {
        int sizeOfPath;
        in.read((char*)&sizeOfPath, sizeof(int));
        listOfFiles.push_back(pathOut);
        listOfFiles[i] += '\\';
        for (int j = 0; j < sizeOfPath; j++) {
            char ch;
            in.read((char*)&ch, sizeof(char));
            listOfFiles[i] += ch;
        }
    }
    return in.tellg();
}

void createDir(std::vector<std::string>listOfFiles) {
    for (int i = 0; i < listOfFiles.size(); i++) {
        if (listOfFiles[i][listOfFiles[i].size() - 1] == 'd') {
            listOfFiles[i].pop_back();
            boost::filesystem::create_directories(listOfFiles[i]);
        }
        else
            listOfFiles[i].pop_back();
    }
}

void prevDir(std::string& dir) {
    int i = dir.size() - 1;
    while (dir[i] != '\\'&&dir[i]!=':') {
        dir.pop_back();
        i--;
    }
    if(dir[dir.size()-2]!=':')
        dir.pop_back();
}
bool rightHFF(std::string str) {
    if (str[str.size() - 1] == 'f' && str[str.size() - 2] == 'f' && str[str.size() - 3] == 'h' && str[str.size() - 4] == '.')
        return true;
    else
        return false;
}