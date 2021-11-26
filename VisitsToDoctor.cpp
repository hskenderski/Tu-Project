#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string.h>
#include "Date.cpp"
#include <list>
using namespace std;
class VisitsToDoctor {
private:
    string egn;
    string name;
    string complaint;
    Date date;
    list<string> oldComplaintAndDiagnose;
    string diagnose;
    list<string> medicines;

public:
    VisitsToDoctor(string egn,string name,string complaint,Date date,string diagnose){
        this->egn=egn;
        this->name = name;
        this->complaint=complaint;
        this->date=date;
        this->diagnose=diagnose;
    }
public:
    VisitsToDoctor()= default;

    const string &getEgn() const {
        return egn;
    }

    void setEgn(const string &egn) {
        VisitsToDoctor::egn = egn;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        VisitsToDoctor::name = name;
    }

    const string &getComplaint() const {
        return complaint;
    }

    void setComplaint(const string &complaint) {
        VisitsToDoctor::complaint = complaint;
    }

    const Date &getDate() const {
        return date;
    }

    void setDate(const Date &date) {
        VisitsToDoctor::date = date;
    }

    const list<string> &getOldComplaintAndDiagnose() const {
        return oldComplaintAndDiagnose;
    }

    void setOldComplaintAndDiagnose(const list<string> &oldComplaintAndDiagnose) {
        VisitsToDoctor::oldComplaintAndDiagnose = oldComplaintAndDiagnose;
    }

    const list<string> &getMedicines() const {
        return medicines;
    }

    void setMedicines(const list<string> &medicines) {
        VisitsToDoctor::medicines = medicines;
    }

    const string &getDiagnose() const {
        return diagnose;
    }

    void setDiagnose(const string &diagnose) {
        VisitsToDoctor::diagnose = diagnose;
    }
};