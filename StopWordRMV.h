#include <iostream> //lenght static or use max length (constructor)
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define maxStopWordsNumber 10 /*when we know how many stop words we have or maximum estimated value of it 
(if we dont know set it to 1 to optimize memory)*/

using namespace std;

class StopWordManager{ 
    private:
        string *stopWordsList;    //totally we use this
        string certainStopWordsNumber[maxStopWordsNumber];  /* *stopWordsList is assigned to this if ... ==> 
        (that maxStopWordsNumber define)*/
        short int numberOfStopWords; //exact number of stop words.   used for sorting.
        string stopWordsListFilePath = "List of StopWords.dat";
        
        void loadStopWordsList(){
            
            try
            {
                ifstream stopWordsFile;
                string newStopWord;
                stopWordsFile.open(stopWordsListFilePath); /*replace it with relative address or difine a directory path
                    and fill it by recieve from user (+define setter) OR retrieve it from .config file (root directory part*/
                
                //after this, numberOfStopWords will match exact number (not one less)
                for(numberOfStopWords=0 ; getline(stopWordsFile,newStopWord) ; numberOfStopWords++){//fill array
                    *(stopWordsList + numberOfStopWords) = newStopWord;
                }
                stopWordsFile.close();
            }
            catch(const exception& e)
            {
                cout<< "it may you setted maxStopWordsNumber more than real value of it OR file open ERROR" <<endl;
            }
            quickSortStringPointerArray(stopWordsList , 0 , numberOfStopWords-1);
        }

        /* gets a pointer to a string array and sortes it with QuickSort Algorithm.
            We use it because we use QuickSeach to find out a word is stop word or not (at isStopWord() function) */
        void quickSortStringPointerArray(string *array,short int head,short int tail){ 
            short int i = head;
            short int j = tail;
            string pivot = array[(i + j) / 2];
            string temp;

            while (i <= j)
            {
                while (array[i].compare(pivot) < 0)
                    i++;
                while (array[j].compare(pivot) > 0)
                    j--;
                if (i <= j)
                {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                    i++;
                    j--;
                }
            }
            if (j > head)
                quickSortStringPointerArray(array, head, j);
            if (i < tail)
                quickSortStringPointerArray(array, i, tail);
        }


    public:
        StopWordManager(){ //this constructor is called when ... ==> (that maxStopWordsNumber define)
            stopWordsList = certainStopWordsNumber;
            loadStopWordsList();
        }
        StopWordManager(int lenght){
            stopWordsList = new string[lenght];
            loadStopWordsList();
        }

        bool isStopWord(string word){ // checks whether a word is stop word or not.
            int i = 0;
            int j = numberOfStopWords - 1;
            while (i < j)
            {

                int mid = i + (j - i) / 2;
                //cout<<i<<" "<<j<<" "<<stopWordsList[mid]<<" "<<word<<endl;
                if (stopWordsList[mid].compare(word) < 0)
                    i = mid + 1;
                else if (stopWordsList[mid].compare(word) > 0)
                    j = mid - 1;
                else
                    return true;
            }
            if (stopWordsList[i].compare(word)==0)
                return true;
            return false;
        }

        //delete stop words form a sequence of words.
        void removeStopWords(string &sentence){ 
            vector<string> inputWords;
            //split(inputWords, sentence, is_any_of("\t "));
            string temp;
            istringstream stringStream(sentence);
            while (getline(stringStream, temp, ' ')) //push all words to inputWords
            {
                inputWords.push_back(temp);
            }
            sentence = "";
            for(int i=0 ; i<inputWords.size() ; i++){  //rebuild query with non stop words
                temp = inputWords.at(i);
                if(!isStopWord(temp))
                    sentence = sentence + " " + temp;
            }
            sentence = sentence.substr(1,sentence.size());//to remove one space at begining because space is inserted before new word
        }
};

//workflow:
//load stop words
//recieve word and say its stop or not   OR  recieve query and send back cleaned text

