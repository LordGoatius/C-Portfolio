#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
#include"Set.h"
#include"HashMap.h"
#include"Pair.h"


#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main(int argc, char* argv[]) {
    VS_MEM_CHECK
        //intalize command line args
        if (argc < 3) {
            cerr << "Please provide name of input and output files";
            return 1;
        }

    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }

    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    Set<string> set;
    HashMap<string, string> pokemon;
    HashMap<string, string> moves;
    HashMap<string, Set<string>> effective;
    HashMap<string, Set<string>> ineffective;


    bool continueMenuLoop = true;
    while (!in.eof()) {
        string line;
        getline(in, line);
        istringstream iss(line);
        string userMenuChoice;
        iss >> userMenuChoice;

        if (userMenuChoice == "Set:") {
            set.clear();
            string input = "";
            while (iss >> input) {
                set.insert(input);
            }
            out << line << endl;
            out << "\t" << set.toString() << endl;;
        }
        else if (userMenuChoice == "Pokemon:") {
            out << line << endl;
            string poke;
            string type;
            iss >> poke;
            iss >> type;
            pokemon[poke] = type;
        }
        else if (userMenuChoice == "Move:") {
            out << line << endl;
            string move;
            string type;
            iss >> move;
            iss >> type;
            moves[move] = type;
        }
        else if (userMenuChoice == "Effective:") {
            out << line << endl;
            string isEffectiveAgainst;
            iss >> isEffectiveAgainst;
            string types;
            while (iss >> types) {
                effective[isEffectiveAgainst].insert(types);
            }
        }
        else if (userMenuChoice == "Ineffective:") {
            out << line << endl;
            string isIneffectiveAgainst;
            iss >> isIneffectiveAgainst;
            string types;
            while (iss >> types) {
                ineffective[isIneffectiveAgainst].insert(types);
            }
        }
        else if (userMenuChoice == "Pokemon") {
            out << "Pokemon: " << pokemon.size() << "/" << pokemon.max_size() << endl;
            out << pokemon << endl;
        }
        else if (userMenuChoice == "Moves") {
            out << "Moves: " << moves.size() << "/" << moves.max_size() << endl;
            out << moves << endl;
        }
        else if (userMenuChoice == "Effectivities") {
            out << "Effectivities: " << effective.size() << "/" << effective.max_size() << endl;
            out << effective << endl;
        }
        else if (userMenuChoice == "Ineffectivities") {
            out << "Ineffectivities: " << ineffective.size() << "/" << ineffective.max_size() << endl;
            out << ineffective << endl;
        }
        else if (userMenuChoice == "Battle:") {
            string pokemonA;
            string attackA;
            string pokemonB;
            string attackB;
            iss >> pokemonA;
            iss >> attackA;
            iss >> pokemonB;
            iss >> attackB;
            int damageAToB = effective[moves[attackA]].count(pokemon[pokemonB])
                - ineffective[moves[attackA]].count(pokemon[pokemonB]);
            int damageBToA = effective[moves[attackB]].count(pokemon[pokemonA])
                - ineffective[moves[attackB]].count(pokemon[pokemonA]);
            out << line << endl;
            out << "\t" << pokemonA << " (" << attackA << ") vs " << pokemonB << " (" << attackB << ")" << endl;
            if (damageAToB == -1) {
                out << "\t" << pokemonA << "'s " << attackA << " is ineffective against " << pokemonB << endl;
            }
            if (damageAToB == 0) {
                out << "\t" << pokemonA << "'s " << attackA << " is effective against " << pokemonB << endl;
            }
            if (damageAToB == 1) {
                out << "\t" << pokemonA << "'s " << attackA << " is super effective against " << pokemonB << endl;
            }

            if (damageBToA == -1) {
                out << "\t" << pokemonB << "'s " << attackB << " is ineffective against " << pokemonA << endl;
            }
            if (damageBToA == 0) {
                out << "\t" << pokemonB << "'s " << attackB << " is effective against " << pokemonA << endl;
            }
            if (damageBToA == 1) {
                out << "\t" << pokemonB << "'s " << attackB << " is super effective against " << pokemonA << endl;
            }
            if (damageAToB == damageBToA) out << "\t" << "The battle between " << pokemonA << " and " << pokemonB << " is a tie." << endl;
            else {
                out << "\t" << "In the battle between " << pokemonA << " and " << pokemonB << ", ";
                if (damageAToB > damageBToA) out << pokemonA << " wins!" << endl;
                if (damageBToA > damageAToB) out << pokemonB << " wins!" << endl;
            }
            
        }
    }
    return 0;
}