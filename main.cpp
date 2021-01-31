#include <sys/wait.h>
#include <unistd.h>
#include <chrono>
#include <iostream>

using namespace std;

string getTimeStr(){
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string s(30, '\0');
    strftime(&s[0], s.size(), "%H:%M:%S", localtime(&now));
    return s;
}
//reference: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono

int main(){
    
    pid_t pid[5]={-1,-1,-1,-1,-1};
    pid[0] = fork();
    
    if(pid[0] > 0){
        string father_birth = getTimeStr();
        time_t father_begin, father_end;
        time(&father_begin);
        cout<<"Nascimento do processo pai "<<"(PID:"<< getpid() <<") "<<"*" << father_birth << endl;
        sleep(14);
        string son1_birth = getTimeStr();
        time_t son1_begin, son1_end;
        time(&son1_begin);
        cout<< "Pai "<<"(PID:"<< getpid() <<") "<<"gerando primeiro filho *" << son1_birth <<" (Nascimento do filho 1)"<<endl;
        pid[1] = fork();
        if(pid[1] > 0){
            sleep(2);
            string son2_birth = getTimeStr();
            time_t son2_begin, son2_end;
            time(&son2_begin);
            cout<< "Pai "<<"(PID:"<< getpid() <<") "<<"gerando segundo filho *" << son2_birth <<" (Nascimento do filho 2)"<<endl;
            pid[2] = fork();
            if(pid[2] == 0){
                sleep(14);
                string grandson2_birth = getTimeStr();
                time_t grandson2_begin, grandson2_end;
                time(&grandson2_begin);
                cout<< "Filho 2 "<<"(PID:"<< getpid() <<") "<<"gerando segundo neto *" << grandson2_birth <<" (Nascimento do neto 2)"<<endl;
                pid[4] = fork();
                if(pid[4] > 0){
                    sleep(16);
                    time(&son2_end);
                    cout<< "Filho 2 "<<"(PID:"<< getpid() <<") "<<"morreu *"<< son2_birth << " †"<<getTimeStr() << " e viveu "<< difftime(son2_end, son2_begin) <<" anos"<<endl;
                    kill(getpid(), SIGTERM);
                }
                if(pid[4] == 0){
                    sleep(18);
                    time(&grandson2_end);
                    cout<<"Neto 2 "<<"(PID:"<< getpid() <<") "<<"morreu *"<< grandson2_birth << " †"<<getTimeStr() << " e viveu "<< difftime(grandson2_end, grandson2_begin) <<" anos"<<endl;
                    kill(getpid(), SIGTERM);
                }
            }
        } if (pid[1] == 0) {
            sleep(12);
            string grandson1_birth = getTimeStr();
            time_t grandson1_begin, grandson1_end;
            time(&grandson1_begin);
            cout<< "Filho 1 "<<"(PID:"<< getpid() <<") "<<"gerando primeiro neto *" << grandson1_birth <<" (Nascimento do neto 1)"<< endl;
            pid[3] = fork();
            if(pid[3] == 0){
                sleep(12);
                time(&grandson1_end);
                cout<<"Neto 1 "<<"(PID:"<< getpid() <<") "<<"morreu *"<< grandson1_birth << " †"<<getTimeStr() << " e viveu "<< difftime(grandson1_end, grandson1_begin) <<" anos"<<endl;
                kill(getpid(), SIGTERM);
            }
            sleep(18);
            time(&son1_end);
            cout<< "Filho 1 "<<"(PID:"<< getpid() <<") "<<"morreu *"<< son1_birth << " †"<<getTimeStr() << " e viveu "<< difftime(son1_end, son1_begin) <<" anos"<<endl;
            kill(getpid(), SIGTERM);
        }
        sleep(44);
        time(&father_end);
        cout<<"Pai "<<"(PID:"<< getpid() <<") "<<"morreu *"<< father_birth << " †"<<getTimeStr() << " e viveu "<< difftime(father_end, father_begin) <<" anos"<<endl;
        kill(getpid(), SIGTERM);
    } 
    return 0;
}
