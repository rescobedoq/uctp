/** * @file uctpv1.0.cpp * * @datetime 2019-10-11 10:14:09 a.m. * * @version 1.0 * * @author Richart Escobedo * Contact: rescobedoq@unsa.edu.pe * * Implementation of a initial solution (of the instances) of Curriculum Based Course Timetabling 2007 * * http://www.cs.qub.ac.uk/itc2007/curriculmcourse/course_curriculm_index.htm *  * structs: course, room, curricula, constraint and assigned. * vectors: coursesVector, roomsVector, curriculaVector, contraintsVector and solutionVector * * This code obtain the initial solution in solutionVector vector. * */#include <bits/stdc++.h>using namespace std;mt19937 Rand (random_device{}()+time(0));struct course{	string courseId;	string teacherName;	int lecturesNumber;	int minWorkingDays;	int studentsNumber;};struct room{	string roomId;	int capacity;};struct curricula{	string curriculumId;	int coursesNumber;	vector<string> membersId;};struct constraint{	string courseId;	int day;	int dayPeriod;};struct solution{	std::vector<std::vector<int>> e; //vector bidimesional mxp};string printDay(int dayId);struct assigned{	string courseId;	string roomId;	int day;	int dayPeriod;};void printEvents(vector<string> events);bool compareEvents(vector<string> e2, vector<string> e1);bool passH2(string e1,string e2, vector<curricula> cV);int main(int argc, char *argv[]) {		//string instancePath = "Datasets/Early/comp01.ctt";	//string instancePath = "Datasets/Late/comp08.ctt";	//string instancePath = "Datasets/Hidden/comp15.ctt";	string instancePath = "Datasets/example.ctt";	ifstream instanceFile (instancePath);	string textName, nameValue;	string textCourses; int coursesNumber;	string textRooms; int roomsNumber;	string textDays; int daysNumber;	string textPeriodsPerDay; int periodsPerDayNumber;	string textCurricula; int curriculaNumber;	string textConstraints; int constraintsNumber;	instanceFile>>textName>>nameValue;		instanceFile>>textCourses>>coursesNumber;	instanceFile>>textRooms>>roomsNumber;	instanceFile>>textDays>>daysNumber;	instanceFile>>textPeriodsPerDay>>periodsPerDayNumber;	instanceFile>>textCurricula>>curriculaNumber;	instanceFile>>textConstraints>>constraintsNumber;	cout<<endl<<"|-----------------------------------------------|";	cout<<endl<<"|"<<"\tCurriculum based Course timetabling\t"<<"|";	cout<<endl<<"|-----------------------------------------------|"<<endl<<endl;	cout<<textName<<" "<<nameValue<<endl;	cout<<textCourses<<" "<<coursesNumber<<endl;	cout<<textRooms<<" "<<roomsNumber<<endl;	cout<<textDays<<" "<<daysNumber<<endl;	cout<<textPeriodsPerDay<<" "<<periodsPerDayNumber<<endl;	cout<<textCurricula<<" "<<curriculaNumber<<endl;	cout<<textConstraints<<" "<<constraintsNumber<<endl;	char showData;	showData='n'; /* y,n */	/* (1) READ COURSES |----------------------------| */	vector<course> coursesVector;	int i;	string line;			getline(instanceFile,line);	getline(instanceFile,line);	struct course courseStruct;		getline(instanceFile,line);	if( tolower(showData)=='y' ){cout<<endl<<line;}	for(i=1;i<=coursesNumber;i++){		instanceFile>>courseStruct.courseId>>courseStruct.teacherName>>courseStruct.lecturesNumber>>courseStruct.minWorkingDays>>courseStruct.studentsNumber;		coursesVector.push_back(courseStruct);	}	if( tolower(showData)=='y' ){cout<<" "<<coursesVector.size()<<endl;}	if( tolower(showData)=='y' ){		for(auto item:coursesVector){			cout<<item.courseId<<"\t"<<item.teacherName<<"\t"<<item.lecturesNumber<<"\t"<<item.minWorkingDays<<"\t"<<item.studentsNumber<<endl;		}	}	/* (2) READ ROOMS |----------------------------| */	vector<room> roomsVector;	getline(instanceFile,line);	getline(instanceFile,line);	struct room roomStruct;		getline(instanceFile,line);	if( tolower(showData)=='y' ){cout<<endl<<line;}	for(i=1;i<=roomsNumber;i++){		instanceFile>>roomStruct.roomId>>roomStruct.capacity;		roomsVector.push_back(roomStruct);	}	if( tolower(showData)=='y' ){cout<<" "<<roomsVector.size()<<endl;}	if( tolower(showData)=='y' ){		for(auto item:roomsVector){			cout<<item.roomId<<"\t"<<item.capacity<<endl;		}	}	/* (3) READ CURRICULA |----------------------------| */	vector<curricula> curriculaVector;	getline(instanceFile,line);	getline(instanceFile,line);	struct curricula curriculaStruct;	int j;	string memberId;		getline(instanceFile,line);	if( tolower(showData)=='y' ){cout<<endl<<line;}	for(i=1;i<=curriculaNumber;i++){		instanceFile>>curriculaStruct.curriculumId>>curriculaStruct.coursesNumber;		curriculaStruct.membersId.clear();		for(j=1;j<=curriculaStruct.coursesNumber;j++){			instanceFile>>memberId;			curriculaStruct.membersId.push_back(memberId);		}		//cout<<endl;		curriculaVector.push_back(curriculaStruct);	}	if( tolower(showData)=='y' ){cout<<" "<<curriculaVector.size()<<endl;}	if( tolower(showData)=='y' ){		for(auto item:curriculaVector){			cout<<item.curriculumId<<"\t"<<item.coursesNumber<<"\t";			for(auto member:item.membersId){				cout<<member<<"\t";			}			cout<<endl;		}	}	/* (4) READ CONSTRAINTS |----------------------------| */	vector<constraint> constraintsVector;	getline(instanceFile,line);	getline(instanceFile,line);	struct constraint constraintStruct;		getline(instanceFile,line);	if( tolower(showData)=='y' ){cout<<endl<<line;}	for(i=1;i<=constraintsNumber;i++){		instanceFile>>constraintStruct.courseId>>constraintStruct.day>>constraintStruct.dayPeriod;		constraintsVector.push_back(constraintStruct);	}	if( tolower(showData)=='y' ){cout<<" "<<constraintsVector.size()<<endl;}	if( tolower(showData)=='y' ){		for(auto item:constraintsVector){			cout<<item.courseId<<"\t"<<item.day<<"\t"<<item.dayPeriod<<endl;		}		cout<<endl;	}	cout<<endl<<"|----------- VECTORS IN MEMORY ---------|";	cout<<endl<<"|\t"<<"coursesVector.size() = "<<coursesVector.size()<<"\t|";	cout<<endl<<"|\t"<<"roomsVector.size() = "<<roomsVector.size()<<"\t\t|";	cout<<endl<<"|\t"<<"curriculaVector.size() = "<<curriculaVector.size()<<"\t|";	cout<<endl<<"|\t"<<"constraintsVector.size() = "<<constraintsVector.size()<<"\t|";	cout<<endl<<"|---------------------------------------|"<<endl;	/* -------- Vector of sets to Initial Solution -------- */	int m=roomsNumber; int p=periodsPerDayNumber;	struct solution solutionStruct;		//Resize daySolution to mxp size	solutionStruct.e.resize(m);	for(i=0; i<m; i++){    solutionStruct.e[i].resize(p);   	}	//Initial solution for one day	int x,y;	for(x=0;x<m;x++){		for(y=0;y<p;y++){			solutionStruct.e[x][y]=-1;		}	}	//Set de initial solutions for all days	vector<solution> X;	for(i=1;i<=daysNumber;i++){				X.push_back(solutionStruct);	}	if( tolower(showData)=='y' ){		cout<<endl;		/**/		int day=0;		/**/		for(auto xi:X){			cout<<"Day : "<<day<<" ("<<printDay(day)<<")";			for(x=0;x<m;x++){				cout<<endl;				for(y=0;y<p;y++){					cout<<"\t"<<xi.e[x][y];				}			}			cout<<endl;			day++;		}	}	cout<<endl<<"|---- X VECTOR FOR INITIAL SOLUTION ----|";	cout<<endl<<"|\t"<<"X.size() = "<<X.size()<<"("<<m<<"x"<<p<<")"<<"\t\t|";	cout<<endl<<"|---------------------------------------|"<<endl;	/* -------- Initial Solution -------- */	//H1'=Room-requirements, H2=Student-clash and H3=Room-clash	vector<assigned> solutionVector;	vector<string> E;	vector<string> E2;	vector<string> binnacle; //bitácora = {}	//E=E2	for(auto item:coursesVector){		E.push_back(item.courseId);		E2.push_back(item.courseId);	}		cout<<endl<<"E = "; printEvents(E);	cout<<"E2 = "; printEvents(E2);	cout<<"binnacle = "; printEvents(binnacle);	//conij Whether event ei and ej have student-clash with each other: 0/1	int n = E.size();	int con[n][n];	for(x=0;x<n;x++){		/**/		if( tolower(showData)=='n' ){			cout<<endl;		}		/**/		for(y=0;y<n;y++){			if(x==y || E[x]==E[y] ){				con[x][y]=0;							}else{				//cout<<endl<<"Evaluate pass H2 :"<<E[x]<<", "<<E[y];				if( passH2(E[x],E[y],curriculaVector) ){					con[x][y]=1;				}else{					con[x][y]=0;				}			}			/**/			if( tolower(showData)=='n' ){				cout<<con[x][y]<<"\t";			}			/**/		}	}	cout<<endl;	bool clash;	while( !compareEvents(E2,binnacle) ){		//randomly select an event (ej) from E2		int randomIndexE2 = Rand() % E2.size();		auto &randomItemE2 = *(E2.begin() + randomIndexE2);		cout<<endl<<"randomIndexE2 = "<<randomIndexE2;		cout<<endl<<"randomItemE2 = "<<randomItemE2;		binnacle.push_back(randomItemE2);		//does not have student-clash : H2 ...ok		clash = true;		if( !clash ){				E2.erase(E2.begin()+randomIndexE2);		}		cout<<endl<<"E2 = "; printEvents(E2);		cout<<"binnacle = "; printEvents(binnacle);	}	return 0;}string printDay(int dayId){	switch(dayId){		case 0: return "Monday"; break;		case 1: return "Tuesday"; break;		case 2: return "Wednesday"; break;		case 3: return "Thursday"; break;		case 4: return "Friday"; break;		case 5: return "Saturday"; break;		case 6: return "Sunday"; break;		default: return "Badday";	}}void printEvents(vector<string> events){	//cout<<endl;	cout<<"{";	int i=0;	for(auto item:events){		i++;		if(i==events.size()){			cout<<item;		}else{			cout<<item<<", ";		}	}	cout<<"}"<<endl;}bool compareEvents(vector<string> e2, vector<string> e1){	for(auto it2:e2){		for(auto it1:e1){			if(it2==it1){				return true;			}		}	}	return false;}bool passH2(string e1,string e2, vector<curricula> cV){	int found;	//cout<<endl<<e1<<"!="<<e2<<" ? ";	if( e1!=e2 ){		//cout<<"true"<<endl;		for(auto item:cV){			found=0;			for(auto member:item.membersId){				//cout<<member<<"\t";				if(member==e1 || member==e2){					found++;				}				if(found==2){					return true;				}			}			//cout<<endl<<"found : "<<found<<endl;					}	}	//cout<<"false"<<endl;	return false;}