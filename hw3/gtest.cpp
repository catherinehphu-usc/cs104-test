/*
    Written by Catherine Phu to test HW3: CS104
*/
# include "gtest/gtest.h"
#include "searcheng.h"
#include "searchui.h"
#include "md_parser.h"
#include "txt_parser.h"
#include "handler.h"
#include "cmdhandler.h"
#include "util.h"
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <fstream> 
#include <iostream> 

using namespace std;


class GitTestSuite : public ::testing::Test {
    protected:
        static void SetUpTestSuite() {
    }
};

void populateVector(vector<string> &v, string filename){
	ifstream myfile(filename); 
	string s; 
	while(getline(myfile,s)){
		v.push_back(s); 
	}
}

testing::AssertionResult existsInVector(vector<string> &v, string term){
	for(unsigned int i=0; i<v.size(); i++){
		if(v[i]==term) return testing::AssertionSuccess(); 
	}
	return testing::AssertionFailure() << "Didn't parse '" << term << "' correctly"; 
}

void checkMDParser(string filename1, string filename2, string filename3){
	MDParser parser; 
    set<string> allSearchableTerms; 
    set<string> allOutgoingLinks;
    vector<string> v; 
    string s; 

    parser.parse(filename1,allSearchableTerms,allOutgoingLinks); 

    populateVector(v,filename2); 

    for(set<string>::iterator it=allSearchableTerms.begin(); it!=allSearchableTerms.end(); ++it){
    	s=*it; 
    	EXPECT_TRUE(existsInVector(v,*it));  
    }
    v.clear(); 

    populateVector(v, filename3);
    for(set<string>::iterator it=allOutgoingLinks.begin(); it!=allOutgoingLinks.end(); ++it){
    	s=*it; 
    	EXPECT_TRUE(existsInVector(v,*it)); 
    }

}

void runSearchEngine(string indexFile, string filename1, string filename2){
	ifstream myinput(filename1);  
	ofstream myoutput(filename2); 

    TXTParser noExtParser; 
    SearchEng seng(&noExtParser);

    TXTParser txtParser; 
    MDParser mdParser; 
    seng.register_parser("txt", &txtParser); 
    seng.register_parser("md", &mdParser); 

    SearchUI ui(&seng); 

    ANDWebPageSetCombiner andSC; 
    ORWebPageSetCombiner orSC; 
    DIFFWebPageSetCombiner diffSC; 

    ui.add_handler(new QuitHandler); 
    ui.add_handler(new PrintHandler); 
    ui.add_handler(new IncomingHandler); 
    ui.add_handler(new OutgoingHandler); 
    ui.add_handler(new ANDHandler(&andSC)); 
    ui.add_handler(new ORHandler(&orSC)); 
    ui.add_handler(new DIFFHandler(&diffSC)); 

    seng.read_pages_from_index(indexFile); 
    ui.run(myinput,myoutput); 
}

void checkSearchEngine(string indexFile, string filename1, string filename2, string filename3){
	vector<string> v1, v2; 
	runSearchEngine(indexFile, filename1, filename2); 
	populateVector(v1, filename2); 
	populateVector(v2, filename3); 

	EXPECT_EQ(v1.size(),v2.size()) << "Failing: " << filename1; 

	for(unsigned int i=0; i<v1.size(); i++){
		EXPECT_TRUE(v1[i]==v2[i]) << "Output: " << v1[i] << "\nExpected: " << v2[i]; 
	}
}


//tests the MDParser with the basic md files given to us 
TEST_F(GitTestSuite, testBasicMDParser) {
	checkMDParser("test-small/page1.md","test-small/page1_text", "test-small/page1_link"); 
	checkMDParser("test-small/page3.md","test-small/page3_text", "test-small/page3_link"); 
}

//tests the MDParser with more advanced edge cases 
TEST_F(GitTestSuite, testAdvancedMDParser){
	checkMDParser("test-small/mdParserTest1.md", "test-small/mdParserTest1_text", "test-small/mdParserTest1_link"); 
	checkMDParser("test-small/mdParserTest2.md", "test-small/mdParserTest2_text", "test-small/mdParserTest2_link"); 
	checkMDParser("test-small/mdParserTest3.md", "test-small/mdParserTest3_text", "test-small/mdParserTest3_link"); 
	checkMDParser("test-small/mdParserTest4.md", "test-small/mdParserTest4_text", "test-small/mdParserTest4_link"); 
	checkMDParser("test-small/mdParserTest5.md", "test-small/mdParserTest5_text", "test-small/mdParserTest5_link"); 
}

//tests the Search Engine with the basic examples provided 
TEST_F(GitTestSuite, basicSearchEngCheck){
	checkSearchEngine("test-small/index.in", "test-small/query1.txt", "test-small/query1_output", "test-small/query1.exp"); 
	checkSearchEngine("test-small/index.in", "test-small/query2.txt", "test-small/query2_output", "test-small/query2.exp");
}

//tests the Search Engine with more advanced edge cases 
TEST_F(GitTestSuite, advancedSearchEngCheck){
	//tests file that doesn't exist 
    EXPECT_THROW(checkSearchEngine("test-small/badFileIndex.in", "test-small/advSearch1.txt", "test-small/advSearch1_output", "test-small/advSearch1.exp"), std::invalid_argument); 
    //tests file with html extension --> should use noExtensionParser_
    checkSearchEngine("test-small/index2.in", "test-small/advSearch1.txt", "test-small/advSearch1_output", "test-small/advSearch1.exp"); 
}




