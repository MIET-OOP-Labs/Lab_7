#include "lesson.h"

lesson::lesson() {
}

lessonStruct lesson::getLessonParams() const {
    return lessonParams;
}

void lesson::setLessonParams(lessonStruct newRecord) {
    lessonParams = newRecord;
}

int lesson::getParamNum() {
    return this->param_num;
}

string lesson::repr() {
    char buff[128] = "";
    sprintf(buff, "ID: %d; Subject: %s; Type: %s; Classroom: %d\n",
            lessonParams.id, lessonParams.subjectName.c_str(),
            getLessonStr(lessonParams.lessonType).c_str(), lessonParams.classroom);
    return string(buff);
}

bool lesson::getLessonFromStr(vector<string> str, lesson &newLesson) {
    lessonStruct currRecord;
    if (str.size() != newLesson.getParamNum()) {
        return false;
    }

    try {
        currRecord.id = stoi(str[0]);
    } catch(std::invalid_argument const& ex) {
        std::cout << "std::invalid_argument::what(): " << ex.what() << " in string " << str[0] << endl;
        return false;
    }

    try {
        currRecord.num = stoi(str[1]);
    }  catch(std::invalid_argument const& ex) {
        std::cout << "std::invalid_argument::what(): " << ex.what() << " in string " << str[1] << endl;
        return false;
    }


    currRecord.subjectName = str[2];
    currRecord.lessonType = getLessonEnum(str[3]);
    try {
        currRecord.classroom = stoi(str[4]);
    }  catch(std::invalid_argument const& ex) {
        std::cout << "std::invalid_argument::what(): " << ex.what() << " in string " << str[4] << endl;
        return false;
    }

    newLesson.setLessonParams(currRecord);
    return true;
}

bool lesson::parseRowsIntoLessons(vector<vector<string>> rows, vector<lesson>& returnLessons) {

    if (!rows.size()) {
        return false;
    }

    for (int it = 0; it < rows.size(); it++) {
        lesson currLesson;
        if (!getLessonFromStr(rows[it], currLesson)) {
            throw CSV_exception(it);
            return false;
        }
        returnLessons.push_back(currLesson);
    }
    return true;
}
