#include "Passenger.h"
#include "Event.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>

bool first_fly = true;

struct mycmp
{
    bool operator()(Event*& p1, Event*& p2)
    {
        return *p1>*p2;
    }
};

struct first_fly_cmp{
    bool operator() (Passenger*& p1, Passenger*& p2){
        if(p1->flight != p2->flight)
            return p1->flight > p2->flight;
        return p1->arrive > p2->arrive;

    }
};



void airport(priority_queue<Event*, vector<Event*>, mycmp> EventQueue, int _case, int sec, int lugg, int pass, ofstream& myfile){
    first_fly = false;
    bool vip_check = false;
    bool online = false;
    if(_case % 2 == 1)
        first_fly = true;

    if(_case % 4 > 1)
        vip_check = true;
    if(_case > 3)
        online = true;

    Passenger* security_counter[sec];
    Passenger* luggage_counter[lugg];

    for(int i = 0; i < sec; i++){
        security_counter[i] = NULL;
    }
    for(int i = 0; i < lugg; i++){
        luggage_counter[i] = NULL;
    }

    int fail_counter = 0;
    int total_wait_time = 0;
    int empty_lug = lugg;
    int empty_sec = sec;
    int count = 0;
    if(first_fly){
        priority_queue<Passenger*, vector<Passenger*>, first_fly_cmp> security_queue;
        priority_queue<Passenger*, vector<Passenger*>, first_fly_cmp> luggage_queue;
        while(!EventQueue.empty()){
            count++;
            Event* current = EventQueue.top();
            EventQueue.pop();
            int time = current->time;

            if(current->type == 0){

                if(online && current->passenger->luggage == 'N'){
                    if(vip_check && current->passenger->VIP == 'V'){
                        continue;
                    }
                    if(empty_sec){
                        EventQueue.push(new Event(time + current->passenger->security_time, 2, *current->passenger));
                        empty_sec--;
                    }
                    else {
                        current->passenger->queue_enter_time = time;
                        security_queue.push(current->passenger);

                    }

                }
                else {
                    if (empty_lug) {
                        EventQueue.push(new Event(time + current->passenger->luggage_time, 1, *current->passenger));
                        empty_lug--;
                    } else {
                        current->passenger->queue_enter_time = time;
                        luggage_queue.push(current->passenger);

                    }
                }

            }

            if(current->type == 1){

                empty_lug++;
                if(vip_check && current->passenger->VIP == 'V'){
                    total_wait_time += (time - current->passenger->arrive);
                    if(time > current->passenger->flight)
                        fail_counter++;
                    /*
                    delete current->passenger;
                    delete current;
                    */
                }
                else{
                    if(empty_sec){
                        EventQueue.push(new Event(time + current->passenger->security_time, 2, *current->passenger));
                        empty_sec--;
                    }
                    else {
                        current->passenger->queue_enter_time = time;

                        security_queue.push(current->passenger);

                    }
                }

                if(!luggage_queue.empty()){
                    Passenger* pass = luggage_queue.top();
                    luggage_queue.pop();
                    EventQueue.push(new Event(time + pass->luggage_time, 1, *pass));
                    empty_lug--;
                }
            }

            if(current->type == 2){

                total_wait_time += (time - current->passenger->arrive);
                empty_sec++;
                if(time > current->passenger->flight)
                    fail_counter++;
                /*
                delete current->passenger;
                delete current;
                */
                if(!security_queue.empty()){
                    Passenger* pass = security_queue.top();
                    security_queue.pop();
                    EventQueue.push(new Event(time + pass->security_time, 2, *pass));
                    empty_sec--;
                }

            }
        }
    }
    else{
        queue<Passenger*> security_queue;
        queue<Passenger*> luggage_queue;
        while(!EventQueue.empty()){
            count++;
            Event* current = EventQueue.top();
            EventQueue.pop();
            int time = current->time;

            if(current->type == 0){

                if(online && current->passenger->luggage == 'N'){
                    if(vip_check && current->passenger->VIP == 'V'){
                        continue;
                    }
                    if(empty_sec){
                        EventQueue.push(new Event(time + current->passenger->security_time, 2, *current->passenger));
                        empty_sec--;
                    }
                    else {
                        current->passenger->queue_enter_time = time;
                        security_queue.push(current->passenger);

                    }

                }
                else {
                    if (empty_lug) {
                        EventQueue.push(new Event(time + current->passenger->luggage_time, 1, *current->passenger));
                        empty_lug--;
                    } else {
                        current->passenger->queue_enter_time = time;
                        luggage_queue.push(current->passenger);

                    }
                }

            }

            if(current->type == 1){

                empty_lug++;
                if(vip_check && current->passenger->VIP == 'V'){
                    total_wait_time += (time - current->passenger->arrive);
                    if(time > current->passenger->flight)
                        fail_counter++;
                    /*
                    delete current->passenger;
                    delete current;
                    */
                }
                else{
                    if(empty_sec){
                        EventQueue.push(new Event(time + current->passenger->security_time, 2, *current->passenger));
                        empty_sec--;
                    }
                    else {
                        current->passenger->queue_enter_time = time;

                        security_queue.push(current->passenger);

                    }
                }

                if(!luggage_queue.empty()){
                    Passenger* pass = luggage_queue.front();
                    luggage_queue.pop();
                    EventQueue.push(new Event(time + pass->luggage_time, 1, *pass));
                    empty_lug--;
                }
            }

            if(current->type == 2){
                total_wait_time += (time - current->passenger->arrive);
                empty_sec++;
                if(time > current->passenger->flight)
                    fail_counter++;
                /*
                delete current->passenger;
                delete current;
                */
                if(!security_queue.empty()){
                    Passenger* pass = security_queue.front();
                    security_queue.pop();
                    EventQueue.push(new Event(time + pass->security_time, 2, *pass));
                    empty_sec--;
                }

            }
        }
    }
    myfile << ((double)total_wait_time / (double)pass) << " " << fail_counter << endl;
}


int main(int argc, char* argv[]) {
    //clock_t start = clock();

    // below reads the input file
    // in your next projects, you will implement that part as well
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }
    //cout << "wtf is this: " << argv[0] << endl;
    //cout << "input file: " << argv[1] << endl;
    //cout << "output file: " << argv[2] << endl;

    // here, perform the input operation. in other words,
    // read the file named <argv[1]>
    ifstream infile(argv[1]);
    string line;
    vector<string> input;
    // process first line
    getline(infile, line);
    //cout << line << endl;
    string token;
    stringstream stream(line);
     int pass;
    stream >> pass;
     int lugg;
    stream >> lugg;
     int sec;
    stream >> sec;
    /*
    getline(stream, token, ' ');
    const int pass = stoi(token);
    getline(stream, token, ' ');
    const int lugg = stoi(token);
    getline(stream, token, ' ');
    const int sec = stoi(token);
    */
    //cout << pass << " " << lugg << " " << sec << endl;
    Passenger* passenger;
//    int max = 0;
    priority_queue<Event*, vector<Event*>, mycmp> EventQueue;
    //priority_queue<Passenger*, vector<Passenger*>, first_fly_cmp> passengers;

    for(int i = 0; i < pass; i++){
        getline(infile, line);
        passenger = new Passenger(line);
        Event* ev = new Event(passenger->arrive, 0, *passenger);
        EventQueue.push(ev);

    }
    ofstream myfile;
    myfile.open (argv[2]);
    for(int k = 0; k < 8; k++){
        airport(EventQueue, k, sec, lugg, pass, myfile);

    }



    myfile.close();

    //clock_t stop = clock();
    //double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    //printf("\nTime elapsed: %.5f\n", elapsed);
    //return 0;

}