#include <iostream>
#include "stoken.h"
#include <queue>
#include <stack>
#include "integer.h"
#include "oper.h"
#include "constants.h"
#include "openparen.h"
#include "closeparen.h"
#include "variable.h"
#include "function.h"
#include "Points.h"
#include "invalidfuncexception.h"
#include "missingparenexception.h"
#include "missingoperatorexception.h"
#include <cmath>
#include <fstream>

using namespace std;

queue<Token*> TokenizedExp(string s);
//Preconditions: string of infix expression to be calculated
//Postconditions: a queue of the infix expression converted into token type
//each letter of the string that is meaningful for the calculaton will be converted into token* type
//by using the queue of Token* pointing to a dynamically allocated child
//object coresponding to the type of each letter
//i.e. number will be converted in Integer object or operrator will be converted to Oper object
//Note:  DOES NOT HANDLE DOUBLE VALUE YET!!

queue<Token*> ShuntingYard(queue<Token*> inputQ);
//Preconditions: queue of Token*, where all Token* are already pointing to Token objects
//Postconditions: queue of Token* containing postfix expression to be calculated.
//This function will translate infix expression into postfix expression based on the Shuntingyard algorithm
//return a queue of Token*

void PrintQ(queue<Token*> printMe);
//Preconditions: will read each element in the queue one by one
//Postconditions: NONE
//This function will travel through the queue each element by each element.
//As it goes through the queue, it will print each element, then pop the front of the queue and repeat until
//the queue is empty.

void PrintStack(stack<Token*> printMe);
//Preconditions: will read each element in the stack one by one
//Postconditions: NONE
//This function will travel through the stack each element by each element.
//As it goes through the stack, it will print each element, then pop the stack and repeat until
//the stack is empty.

double Eval(queue<Token*> evalThis, double valueofVar = 0.0);
//Preconditions: postfix expression contained in a queue of Token* without any token of OpenParen or CloseParen type.
//Postconditions: a double value as the answer of the calculation on the expression
// This function will travel into the expression and calculate the expression until the expression queue is empty.
// It will push into a number stack when detecting an Integer object.
// If it comes across an Oper object, it will pop a number or two from the number stack for calculation and push the answer back to the stack.
// Once the expression queue is empty, the number stack will have one number left and return that number.

double EvalFunction(Token* tkHold, double value);
//Preconditions: a value and a token of Function type (as in sin, cos, etc.)
//Postconditions: a double value calculated based on the Function and the value.
//will read function and calculate in degrees
//This function will allow the Eval function to handle Function token

bool CheckForVar(queue<Token*> checkThis);
//Preconditions: a queue of Token* that points to an expression containing variable type.
//Postconditions: true of there's any variable else return false
//This function travels through the queue and check each element for Variable type token

void CleanUp(queue<Token*> cleanThis);
//Preconditions: queue of Token* which allocates memory space to store postfix expression
//Postconditions: memery space allcated by the queue freed up
//This will call delete function to release whatever value each Token* of the queue is allocating

void GetSVGGraph(queue<Points*> coordsSet, string fileName = "outFile.svg");
//Preconditions: queue of Points object containing multiple coordinates to be graphed and a filename assuming as that of .svg
//Postconditions: write a svg file through ofstream object.  there's a line graph within the svg file
//This function will read through the queue of points and send it into the file, whose name assigned by the user

void Test();

void Test2(string s);

void Test3();

int main()
{
    cout<< endl<<endl<<endl<<"================"<<endl<<endl;

    char choice = 'y';
    string expression;

    try{
        while(choice == 'y' || choice == 'Y'){
            cout<< "Please enter your expression here: ";
            cin >> expression;
            Test();

            cout<< "Continue? Y/N: ";
            cin >> choice;
        }
    }
    catch(InvalidFuncException f){
        cout<<"Invalid function found in the expression."<<endl;
        f.GetInvalidFunc();
        cout<<endl<<endl;
    }
    catch(MissingParenException p){
        cout<<"The expression contains missing paren."<<endl;
        p.GetMissing();
        cout<<endl<<endl;
    }
    catch(MissingOperatorException o){
        o.GetExtraNumber();
        cout<<endl<<endl;
    }
    cout<< endl<<"================"<<endl<<endl;
    return 0;
}

queue<Token*> TokenizedExp(string s)
{
    queue<Token*> temp;
    STokenize stk(s);
    Token holdToken;

    while(stk.More())
    {
        Token* holdTokPtr;
        holdToken = stk.NextToken();
        switch (holdToken.Type()) {
        case INTEGER:
            holdTokPtr = new Integer(holdToken.TokenString());
            temp.push(holdTokPtr);
            break;
        case OPER:
            holdTokPtr = new Oper(holdToken.TokenString());
            temp.push(holdTokPtr);
            break;
        case LPAREN:
            holdTokPtr = new OpenParen(holdToken.TokenString());
            temp.push(holdTokPtr);
            break;
        case RPAREN:
            holdTokPtr = new CloseParen(holdToken.TokenString());
            temp.push(holdTokPtr);
            break;
        case VARIABLE:
            holdTokPtr = new Variable(holdToken.TokenString());
            temp.push(holdTokPtr);
            break;
        case FUNC:
            holdTokPtr = new Function(holdToken.TokenString());
            temp.push(holdTokPtr);
            break;
        default:
            break;
        }
    }
    return temp;
}

queue<Token*> ShuntingYard(queue<Token*> InputQ){
    queue<Token*> temp;
    stack<Token*> operStack;

    while(!InputQ.empty()){
        Token* hold = InputQ.front();
        switch (hold->TypeOf()) {
        case INTEGER: // push to output q and pop out of input q
            temp.push(InputQ.front());
            InputQ.pop();
            break;
        case OPER://compare presidence of top.
            //If the current operator has equal presidence, pop the top and push to output q
            //then push the current operator to stack
            //(Note: if same presidence and same operator then just push to stack)
            //If the current operator has less presidence value than the top of oper stack, push into outputq immediately
            //makes sure stack is not empty when you front or pop
            //If higher, push to oper stack
            if(operStack.empty()){
                operStack.push(InputQ.front());
                InputQ.pop();
            }
            else{
                Token* atTop;
                atTop = operStack.top();
                if(atTop->TypeOf() == LPAREN){ // check whether if the top of operStack is open paren
                    operStack.push(InputQ.front());
                    InputQ.pop();
//                    cout<< "LParen Detected Insert operStack"<<endl;
                }

                if(static_cast<Oper*>(hold)->PresidenceVal() <= static_cast<Oper*>(atTop)->PresidenceVal()){
                    //if current has lower presidence, pop anything higher
                    //if open paren found push it to stack and dont pop anything

                    if(static_cast<Oper*>(hold)->PresidenceVal() == static_cast<Oper*>(atTop)->PresidenceVal()){
                        //power case
                        if(static_cast<Oper*>(hold)->MyOper() == '^'){
                            operStack.push(InputQ.front());
                            InputQ.pop();
                        }
                    }
                    if(static_cast<Oper*>(operStack.top())->TypeOf() != 3){
                        //other operator
                        while(static_cast<Oper*>(InputQ.front())->PresidenceVal() <= static_cast<Oper*>(operStack.top())->PresidenceVal()){
                            temp.push(operStack.top());
                            operStack.pop();
                            if (operStack.empty())
                                break;
                            if (static_cast<Oper*>(operStack.top())->TypeOf() != 2)
                                break;
                        }
                        operStack.push(InputQ.front());
                        InputQ.pop();
                    }
                }
                else
                {
                    operStack.push(InputQ.front());
                    InputQ.pop();
                }
            }
            break;
        case LPAREN:// push to stack
            operStack.push(InputQ.front());
            InputQ.pop();
            break;
        case RPAREN://pop all OPERATOR tokens and push into output q, up to left paren
            //pop the left paren.
            //makes sure stack is not empty when you front or pop
            Token* flag;
            flag = operStack.top();
            while(flag->TypeOf() != 3)//check for OpenParen
            {
                temp.push(operStack.top());
                operStack.pop();
                if(operStack.empty())
                    throw MissingParenException(static_cast<CloseParen*>(hold)->RParen());
                flag = operStack.top();

            }
            //clean up left paren token here
            delete operStack.top();
            operStack.pop();
            //clean up right paren token here
            delete InputQ.front();
            InputQ.pop();
            break;
        case VARIABLE:
            temp.push(InputQ.front());
            InputQ.pop();
            break;
        case FUNC:
            if(operStack.empty()){
                operStack.push(InputQ.front());
                InputQ.pop();
            }else{
                Token * atTop;
                atTop = operStack.top();
                if(atTop->TypeOf() == 5){// check whether the top of stack is a function or operator
                    // if a function then pop the stack and push the front to stack
                    temp.push(operStack.top());
                    operStack.pop();
                    operStack.push(InputQ.front());
                    InputQ.pop();
                }
                else{
                    // if not then push to stack
                    operStack.push(InputQ.front());
                    InputQ.pop();
                }
            }
            break;
        default:
            break;
        }
    }

    while(!operStack.empty()){ // keep pushing until stack is empty
        temp.push(operStack.top());
        operStack.pop();
    }

    return temp;
}

void PrintQ(queue<Token*> printMe){
    cout<<"{ ";
    while(!printMe.empty()){
        Token *hold = printMe.front();
        hold->Print();
        printMe.pop();
    }
    cout<<" }"<<endl;
}

void PrintStack(stack<Token*> printMe){
    cout<<"{ ";
    while(!printMe.empty()){
        Token *hold = printMe.top();
        hold->Print();
        printMe.pop();
    }
    cout<<" }"<<endl;
}

double Eval(queue<Token*> evalThis, double valueofVar)
{
    stack<double>val;
    double prev, b4prev;
    Token* hold;

    while(!evalThis.empty())
    {
        hold = evalThis.front();
        switch (hold->TypeOf()) {
        case INTEGER:
            val.push((double)static_cast<Integer*>(evalThis.front())->MyInt());
            evalThis.pop();
            break;
        case OPER:
            prev = val.top();
            val.pop();
            b4prev = val.top();
            if(static_cast<Oper*>(hold)->PresidenceVal() == 1){//case '+' or '-'
                if(static_cast<Oper*>(hold)->MyOper() == '+'){
                    val.top() = b4prev + prev;
                }
                else{
                    val.top() = b4prev - prev;
                }
            }
            if(static_cast<Oper*>(hold)->PresidenceVal() == 2){//case '*' or '/'
                if(static_cast<Oper*>(hold)->MyOper() == '*'){
                    val.top() = b4prev * prev;
                }
                else{
                    val.top() = b4prev / prev;
                }
            }
            if(static_cast<Oper*>(hold)->PresidenceVal() == 3){// case '^'
                val.top() = pow(b4prev, prev);
            }
            evalThis.pop();
            break;
        case FUNC:
            prev = val.top();
            if(static_cast<Function*>(hold)->PresidenceVal() == 5){
                val.top() = EvalFunction(hold, prev);
                evalThis.pop();
            }
            else if(static_cast<Function*>(hold)->PresidenceVal() == 4){
                val.top() = sqrt(prev);
                evalThis.pop();
            }

            else
                throw InvalidFuncException(static_cast<Function*>(hold)->MyFunc());
            break;
        case VARIABLE:
            val.push(valueofVar);
            evalThis.pop();
            break;
        case LPAREN:
            throw MissingParenException(static_cast<OpenParen*>(hold)->LParen());
            break;
        default:
            break;
        }
    }
    if(val.size()>1)
        if(hold->TypeOf() == INTEGER)
            throw MissingOperatorException(static_cast<Integer*>(hold)->MyInt());
        else
            throw MissingOperatorException(static_cast<Variable*>(hold)->MyVar());
    else
        return val.top();
}

double EvalFunction(Token* tkHold, double value){
    const double PI = 3.14159265359;
    string s = static_cast<Function*>(tkHold)->MyFunc();
    if(s == "sin")
        return sin(value*PI/180);
    if(s == "cos")
        return cos(value*PI/180);
    if(s == "tan")
        return tan(value*PI/180);
    if(s == "csc")
        return 1/sin(value*PI/180);
    if(s == "sec")
        return 1/cos(value*PI/180);
    if(s == "cot")
        return 1/ tan(value*PI/180);
}

bool CheckForVar(queue<Token*> checkThis){
    Token* hold = checkThis.front();
    while(hold->TypeOf() != VARIABLE){
        checkThis.pop();
        hold = checkThis.front();
        if(checkThis.empty())
            return false;
    }
    return true;
}

void CleanUp(queue<Token*> cleanThis){
    while(!cleanThis.empty()){
        delete cleanThis.front();
        cleanThis.pop();
    }
}

void GetSVGGraph(queue<Points*> coordsSet, string fileName){
    ofstream fout;
    cout<< "Writing into "<< fileName<<endl;
        fout.open(fileName.c_str());
        if (fout.fail())
        {
            cout << "outFile.svg failed to open.";
            exit(1);
        }
        fout << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
        fout << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"" << endl;
        fout << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
        fout << "<svg width=\"2000\" height=\"2000\"\n";
        fout << "xmlns=\"http://www.w3.org/2000/svg\">\n\n";
        fout << "<svg width=\"400px\" height=\"400px\" viewBox=\"0 0 400 400\">\n";
        fout << "<!-- axes -->" << endl;
        fout << "<line x1=\"0\" y1=\"400\" x2=\"400\" y2=\"400\" style=\"stroke: black;\"/>\n";
        fout << "<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"400\" style=\"stroke: black;\"/>\n";
        fout << "<polyline points = \"";
        while(!coordsSet.empty()){
            Points* temp = coordsSet.front();
            fout << (temp->getX()*20.0) << "," << (400-temp->getY()) << " ";
            coordsSet.pop();
        }
        fout << "\"\n";
        fout << "style=\"fill:none;stroke:red;stroke-width:2;\"/>\n";
        fout << "</svg>\n";
        fout.close();
        cout<< "Writing successful!!"<<endl;
}

void Test(){
    try{
        queue<Token*> InputQ, OutputQ;

        string s ="23+15+(san(x))+9";

        try{
            InputQ = TokenizedExp(s);
            cout<< "Infix Queue: ";
            PrintQ(InputQ);

            OutputQ = ShuntingYard(InputQ);
            cout<<endl<< "Postfix Queue: ";
            PrintQ(OutputQ);

            double ans = Eval(OutputQ);
            printf( "The answer is: %.10f\n\n\n",ans);
            CleanUp(OutputQ);
        }
        catch(InvalidFuncException f){
            cout<<"Invalid function found in the expression."<<endl;
            f.GetInvalidFunc();
            cout<<endl<<endl;
        }
        catch(MissingParenException p){
            cout<<"The expression contains missing paren."<<endl;
            p.GetMissing();
            cout<<endl<<endl;
        }

        s = "sin(15)+((11+2)";
        try{
            InputQ = TokenizedExp(s);
            cout<< "Infix Queue: ";
            PrintQ(InputQ);

            OutputQ = ShuntingYard(InputQ);
            cout<<endl<< "Postfix Queue: ";
            PrintQ(OutputQ);

            double ans = Eval(OutputQ);
            printf( "The answer is: %.10f\n\n\n",ans);
            CleanUp(OutputQ);
        }
        catch(InvalidFuncException f){
            cout<<"Invalid function found in the expression."<<endl;
            f.GetInvalidFunc();
            cout<<endl<<endl;
        }
        catch(MissingParenException p){
            cout<<"The expression contains missing paren."<<endl;
            p.GetMissing();
            cout<<endl<<endl;
        }
        s ="3+4*2/(1-5)^2^3";

        InputQ = TokenizedExp(s);
        cout<< "Infix Queue: ";
        PrintQ(InputQ);

        OutputQ = ShuntingYard(InputQ);
        cout<<endl<<"Postfix order expected:{ [3] [4] [2] (*) [1] [5] (-) [2] [3] (^) (^) (/) (+) }"<<endl;
        cout<<endl<< "Postfix Queue: ";
        PrintQ(OutputQ);

        double ans = Eval(OutputQ);
        printf( "The answer is: %.10f\n\n\n",ans);
        CleanUp(OutputQ);


        s = "5/8/3*222-(5/8^0)";
        InputQ = TokenizedExp(s);
        cout<< "Infix Queue: ";
        OutputQ = ShuntingYard(InputQ);

        cout<<endl<<"Postfix order expected:{ [5] [8] (/) [3] (/) (222) (*) [5] [8] [] (^) (/) (-) }"<<endl;
        cout<<endl<< "Postfix Queue: ";
        PrintQ(OutputQ);

        ans = Eval(OutputQ);
        printf( "The answer is: %.10f\n\n\n",ans);
        CleanUp(OutputQ);


        s = "3*3-5+8*2";
        InputQ = TokenizedExp(s);
        cout<< "Infix Queue: ";
        PrintQ(InputQ);
        OutputQ = ShuntingYard(InputQ);

        cout<<endl<<"Postfix order expected:{ [3] [3] (*) [5] (-) [8] [2] (*) (+) }"<<endl;
        cout<<endl<< "Postfix Queue: ";
        PrintQ(OutputQ);

        ans = Eval(OutputQ);
        printf( "The answer is: %.10f\n\n\n",ans);
        CleanUp(OutputQ);


        s= "(sin(30))*5";
        InputQ = TokenizedExp(s);
        cout<< "Infix Queue: ";
        PrintQ(InputQ);
        OutputQ = ShuntingYard(InputQ);

        cout<<endl<<"Postfix order expected:{ [30] (sin) [5] (*) }"<<endl;
        cout<<endl<< "Postfix Queue: ";
        PrintQ(OutputQ);
        if(!CheckForVar(OutputQ)){
            ans = Eval(OutputQ);
            printf( "The answer is: %.10f\n\n\n",ans);
        }
        else{
            queue<Points*> coords4graph;
            Points* hold;
            for(double i = 0; i<= 360; i+=15){
                coords4graph.push(new Points(i));
                hold = coords4graph.back();
                hold->setY(Eval(OutputQ, hold->getX()));
                cout<< *hold<<endl;
            }
            CleanUp(OutputQ);
        }

        s= "(sin(x))+10";
        InputQ = TokenizedExp(s);
        cout<< "Infix Queue: ";
        PrintQ(InputQ);
        OutputQ = ShuntingYard(InputQ);

        cout<<endl<<"Postfix order expected:{ [x] (sin) [10] (+) }"<<endl;
        cout<<endl<< "Postfix Queue: ";
        PrintQ(OutputQ);

        if(!CheckForVar(OutputQ)){
            ans = Eval(OutputQ);
            printf( "The answer is: %.10f\n\n\n",ans);
        }
        else{
            queue<Points*> coords4graph;
            Points* hold;
            for(double i = 0; i<= 360; i+=15){
                coords4graph.push(new Points(i));
                hold = coords4graph.back();
                hold->setY(Eval(OutputQ, hold->getX()));
                cout<< "x = "<<hold->getX()<< "\tf(x) = "<< hold->getY()<<endl;
            }
            CleanUp(OutputQ);
        }


        s= "(x^2)+2*x";
        InputQ = TokenizedExp(s);
        cout<< "Infix Queue: ";
        PrintQ(InputQ);
        OutputQ = ShuntingYard(InputQ);

        cout<<endl<< "Postfix Queue: ";
        PrintQ(OutputQ);

        if(!CheckForVar(OutputQ)){
            ans = Eval(OutputQ);
            printf( "The answer is: %.10f\n\n\n",ans);
        }
        else{
            queue<Points*> coords4graph;
            Points* hold;
            for(double i = 0; i<= 10; i+=0.1){
                coords4graph.push(new Points(i));
                hold = coords4graph.back();
                hold->setY(Eval(OutputQ, hold->getX()));
                cout<< "x = "<<hold->getX()<< "\tf(x) = "<< hold->getY()<<endl;
            }
            GetSVGGraph(coords4graph);
            CleanUp(OutputQ);
        }

    }
    catch(InvalidFuncException f){
        cout<<"Invalid function found in the expression."<<endl;
        f.GetInvalidFunc();
        cout<<endl<<endl;
    }
    catch(MissingParenException p){
        cout<<"The expression contains missing paren."<<endl;
        p.GetMissing();
        cout<<endl<<endl;
    }
}

void Test2(string s){
    queue<Token*> InputQ, OutputQ;
    double ans = 0.0;
    InputQ = TokenizedExp(s);
    cout<< "Infix Queue: ";
    PrintQ(InputQ);

    OutputQ = ShuntingYard(InputQ);
    cout<<endl<< "Postfix Queue: ";
    PrintQ(OutputQ);
    if(!CheckForVar(OutputQ)){
        ans = Eval(OutputQ);
        printf( "The answer is: %.10f\n\n\n",ans);
    }
    else{
        queue<Points*> coords4graph;
        Points* hold;
        for(double i = 0; i<= 30; i+=0.1){
            coords4graph.push(new Points(i));
            hold = coords4graph.back();
            hold->setY(Eval(OutputQ, hold->getX()));
            cout<< "x = "<<hold->getX()<< "\tf(x) = "<< hold->getY()<<endl;
        }
        GetSVGGraph(coords4graph);
        CleanUp(OutputQ);
    }
}

void Test3(){
    Test();
    string s1 = "(tan(x)/sin(x))+(100-x^2)^(1/2)";
    string s2 = "sin(cos(tan(x)))+10";
    string s3 = "3*3-5+8*2";
    string s4 = "sin(x)+cos(3*x)";
    string s5 = "sqrt(1-x^2)";
    string s6 = "sqrt(5/100-(x-3/10)^2)+5/10";
    string s7 = "15*x^2";
    string s8 = "x*sin(1/x)";
    string s9 = "1/(x^3)";
    string s10 = "sin(x+9)+cos(6)^543";
    string s11 = "sin(2*sin(2*sin(2*sin(x))))";
    string s12 = "sin(2*sin2*sin(2*sin(x)))";
    string s13 = "(3+5+(9+2)))";
    string s14 = "3.5.6+2";
    string s15 = "3*+5";
    string s16 = "x5+6";

    char choice = 'y';
    int expression = 0;


    try{
        while(choice == 'y' || choice == 'Y'){
            cout<< "Please choose an expression: ";
            cin >> expression;
            switch (expression) {
            case 1:
                Test2(s1);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 2:
                Test2(s2);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 3:
                Test2(s3);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 4:
                Test2(s4);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 5:
                Test2(s5);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 6:
                Test2(s6);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 7:
                Test2(s7);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 8:
                Test2(s8);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 9:
                Test2(s9);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 10:
                Test2(s10);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 11:
                Test2(s11);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 12:
                Test2(s12);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 13:
                Test2(s13);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 14:
                Test2(s14);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 15:
                Test2(s15);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            case 16:
                Test2(s16);
                cout<<"Continue? Y/N: ";
                cin >> choice;
                break;
            default:
                cout<< "Invalid input"<<endl<<"Continue? Y/N: ";
                cin>> choice;
                break;
            }
        }
    }
    catch(InvalidFuncException f){
        cout<<"Invalid function found in the expression."<<endl;
        f.GetInvalidFunc();
        cout<<endl<<endl;
    }
    catch(MissingParenException p){
        cout<<"The expression contains missing paren."<<endl;
        p.GetMissing();
        cout<<endl<<endl;
    }
    catch(MissingOperatorException o){
        o.GetExtraNumber();
        cout<<endl<<endl;
    }
}

