#include "HashUtils.h"

#include "HashUtils.h"

int main() {
    vector<string> nameVector;
    nameVector.push_back("Ada Rodriguez");
    nameVector.push_back("Rosa Jefferson");
    nameVector.push_back("Jeffrey Mendez");
    nameVector.push_back("Lester Hart");
    nameVector.push_back("Eunice Moran");
    nameVector.push_back("Ina Wilkins");
    nameVector.push_back("Nettie Bowman");
    nameVector.push_back("Belle Cole");
    nameVector.push_back("Elizabeth Wilson");
    nameVector.push_back("Blake Bush");
    nameVector.push_back("Mabel Mason");
    nameVector.push_back("Ora Weber");
    nameVector.push_back("Rodney Love");
    nameVector.push_back("Cole Ross");
    nameVector.push_back("Max Kelly");
    nameVector.push_back("Elnora Spencer");
    nameVector.push_back("Adele Bridges");
    nameVector.push_back("Norman Stevenson");
    nameVector.push_back("Dora Flowers");
    nameVector.push_back("Tillie Gomez");
    nameVector.push_back("Carlos Gordon");
    nameVector.push_back("Augusta Schmidt");
    nameVector.push_back("Mike Holmes");
    nameVector.push_back("Howard Fernandez");
    nameVector.push_back("Mabelle Sutton");
    nameVector.push_back("Leila Baldwin");
    nameVector.push_back("Laura Duncan");
    nameVector.push_back("Isaac Waters");
    nameVector.push_back("Dorothy Maldonado");
    nameVector.push_back("Maurice Howard");
    nameVector.push_back("Jeffrey Ramsey");
    nameVector.push_back("Maria Sherman");
    nameVector.push_back("Sophia Norman");
    nameVector.push_back("Louise Allison");
    nameVector.push_back("Shane Atkins");
    nameVector.push_back("Florence Pope");
    nameVector.push_back("Connor Fleming");
    nameVector.push_back("Marion Austin");
    nameVector.push_back("Fred Fowler");
    nameVector.push_back("Nancy Austin");
    nameVector.push_back("Delia Soto");
    nameVector.push_back("Mary Massey");
    nameVector.push_back("Eugene Alvarado");
    nameVector.push_back("Lucile Ruiz");
    nameVector.push_back("Jerome Wilkins");
    nameVector.push_back("Frank Colon");
    nameVector.push_back("Chris Oliver");
    nameVector.push_back("Lina Bradley");
    nameVector.push_back("Lucille McBride");
    nameVector.push_back("Gregory Mann");
    nameVector.push_back("Johnny Lyons");
    nameVector.push_back("Jayden Ward");
    nameVector.push_back("Fred Stevenson");
    nameVector.push_back("Jeff Pearson");
    nameVector.push_back("Elnora Adams");
    nameVector.push_back("Rosetta Brady");
    nameVector.push_back("Virginia Williams");
    nameVector.push_back("Bernice Drake");
    nameVector.push_back("Marie Evans");
    nameVector.push_back("Francis Doyle");
    nameVector.push_back("Sally Francis");
    nameVector.push_back("Mathilda Marshall");
    nameVector.push_back("Abbie Olson");
    nameVector.push_back("Hettie Clayton");
    nameVector.push_back("Etta Shaw");
    nameVector.push_back("Catherine Graves");
    nameVector.push_back("Jim Carpenter");
    nameVector.push_back("Leila Ward");
    nameVector.push_back("Derrick Blake");
    nameVector.push_back("Julian Parsons");
    nameVector.push_back("Madge Collins");
    nameVector.push_back("Nora Mitchell");
    nameVector.push_back("Luke Sherman");
    nameVector.push_back("Julia Jimenez");
    nameVector.push_back("Glenn Harrison");
    nameVector.push_back("Franklin Pierce");
    nameVector.push_back("Susan Byrd");
    nameVector.push_back("Ethan Oliver");
    nameVector.push_back("Belle Little");
    nameVector.push_back("Polly Castro");
    nameVector.push_back("Lora Fitzgerald");
    nameVector.push_back("Clara Freeman");
    nameVector.push_back("Ricardo Lowe");
    nameVector.push_back("Dean Bennett");
    nameVector.push_back("Arthur Turner");
    nameVector.push_back("Anne Kim");
    nameVector.push_back("Calvin Ramirez");
    nameVector.push_back("May Robertson");
    nameVector.push_back("Stephen Nguyen");
    nameVector.push_back("Gary McBride");
    nameVector.push_back("Steve Gilbert");
    nameVector.push_back("Augusta Brooks");
    nameVector.push_back("Winnie Vasquez");
    nameVector.push_back("Elnora Tran");
    nameVector.push_back("Sylvia Baldwin");
    nameVector.push_back("Chris Cooper");
    nameVector.push_back("Ricardo Curry");
    nameVector.push_back("Rosa Torres");
    nameVector.push_back("Ann Malone");
    nameVector.push_back("Robert Greene");

    HashStringTable ht;

    HashUtils hu;

    hu.addNameList(nameVector);
    hu.deleteName("Ada Rodriguez");

    return 0;
}