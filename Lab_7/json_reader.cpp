#include "json_reader.h"

JSON_Reader::JSON_Reader() {
    readRowNum = 0;
}

void JSON_Reader::openFile(const string fileName){
    file.open(fileName);
    try {
        file >> json;
    }
    catch (nlohmann::json::exception& json) {
        cout << json.what() << '\n';
    }
}

vector<lesson> JSON_Reader::readAllFile(){

    vector<lesson> returnLessonVec;
    vector<vector<string>> JSON_rows;

    for (auto& it: json){
        vector<string> row;
        string str;
        int num;
        try {
            it.at("id").get_to(num);
            row.push_back(to_string(num));

            it.at("num").get_to(num);
            row.push_back(to_string(num));

            it.at("subjectName").get_to(str);
            row.push_back(str);

            it.at("lessonType").get_to(str);
            row.push_back(str);

            it.at("classroom").get_to(num);
            row.push_back(to_string(num));
        }
        catch (nlohmann::json::exception& it) {
            cout << it.what() << '\n';
        }
        JSON_rows.push_back(row);

    }

    lesson::parseRowsIntoLessons(JSON_rows, returnLessonVec);

    return returnLessonVec;
}

bool JSON_Reader::operator>>(lesson& lessonToWrite) {
    if (!(json[readRowNum].empty())){
        vector<string> row;
        string str;
        int num;
        try {
            json[readRowNum].at("id").get_to(num);
            row.push_back(to_string(num));

            json[readRowNum].at("num").get_to(num);
            row.push_back(to_string(num));

            json[readRowNum].at("subjectName").get_to(str);
            row.push_back(str);

            json[readRowNum].at("lessonType").get_to(str);
            row.push_back(str);

            json[readRowNum].at("classroom").get_to(num);
            row.push_back(to_string(num));
        }
        catch (nlohmann::json::exception& it) {
            cout << it.what() << '\n';
        }
        if (!lesson::getLessonFromStr(row, lessonToWrite)) {
            return false;
        }

        readRowNum++;

        return true;
    } else {
        file.close();
        return false;
    }
}


JSON_Reader::~JSON_Reader(){
}
