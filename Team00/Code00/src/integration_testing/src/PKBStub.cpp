#include "./../../spa/src/PKB.h"

class PKBStub: public PKB
{
public:
    PKBStub()
    {
        insert_procedure("main");

        insert_assign(1, "flag", "0");
        insert_variable("flag");
        insert_modifies(1, "flag");
        insert_modifies("main", "flag");
        insert_type(1, EntityType::ASSIGN);

        // insert_call(2, "computeCentroid");
        insert_type(2, EntityType::CALL);
        insert_follows(1, 2);

        // insert_call(3, "printResults");
        insert_type(3, EntityType::CALL);
        insert_follows(2, 3);

        insert_procedure("readPoint");

        insert_type(4, EntityType::READ);
        insert_modifies(4, "x");
        insert_modifies("readPoint", "x");
        insert_variable("x");

        insert_type(5, EntityType::READ);
        insert_modifies(5, "y");
        insert_modifies("readPoint", "y");
        insert_variable("y");
        insert_follows(4, 5);

        insert_procedure("printResults");

        insert_type(6, EntityType::PRINT);
        insert_uses(6, "flag");
        insert_uses("printResults", "flag");
        insert_variable("flag");
        insert_follows(5, 6);

        insert_type(7, EntityType::PRINT);
        insert_uses(7, "cenX");
        insert_uses("printResults", "cenX");
        insert_variable("cenX");
        insert_follows(6, 7);

        insert_type(8, EntityType::PRINT);
        insert_uses(8, "cenY");
        insert_uses("printResults", "cenY");
        insert_variable("cenY");
        insert_follows(7, 8);

        insert_type(9, EntityType::PRINT);
        insert_uses(9, "normSq");
        insert_uses("printResults", "normSq");
        insert_variable("normSq");
        insert_follows(8, 9);

        insert_procedure("computeCentroid");

        insert_assign(10, "count", "0");
        insert_variable("count");
        insert_modifies(10, "count");
        insert_modifies("computeCentroid", "count");
        insert_type(10, EntityType::ASSIGN);

        insert_assign(11, "cenX", "0");
        insert_variable("cenX");
        insert_modifies(11, "cenX");
        insert_modifies("computeCentroid", "cenX");
        insert_type(11, EntityType::ASSIGN);
        insert_follows(10, 11);

        insert_assign(12, "cenY", "0");
        insert_variable("cenY");
        insert_modifies(12, "cenY");
        insert_modifies("computeCentroid", "cenY");
        insert_type(12, EntityType::ASSIGN);
        insert_follows(11, 12);

        // insert_call(13, "readPoint");
        insert_type(13, EntityType::CALL);
        insert_follows(12, 13);

        insert_type(14, EntityType::WHILE);
        insert_uses(14, "x");
        insert_uses(14, "y");
        insert_uses("computeCentroid", "x");
        insert_uses("computeCentroid", "y");
        insert_follows(13, 14);

        insert_type(15, EntityType::ASSIGN);
        insert_variable("count");
        insert_uses(15,  "count");
        insert_modifies(15, "count");
        insert_modifies("computeCentroid", "count");
        insert_uses("computeCentroid",  "count");
        insert_uses(14,  "count");
        insert_modifies(14, "count");
        insert_assign(15, "count", "count + 1");
        insert_parent(14, 15);

        insert_type(16, EntityType::ASSIGN);
        insert_variable("cenX");
        insert_variable("x");
        insert_uses(16,  "cenX");
        insert_uses(16,  "x");
        insert_modifies(16, "cenX");
        insert_uses("computeCentroid",  "cenX");
        insert_uses("computeCentroid",  "x");
        insert_modifies("computeCentroid", "cenX");
        insert_uses(14, "cenX");
        insert_uses(14,  "x");
        insert_modifies(14, "cenX");
        insert_assign(16, "cenX", "cenX + x");
        insert_parent(14, 16);
        insert_follows(14, 15);

        insert_type(17, EntityType::ASSIGN);
        insert_variable("cenY");
        insert_variable("y");
        insert_uses(17,  "cenY");
        insert_uses(17,  "y");
        insert_modifies(17, "cenY");
        insert_uses("computeCentroid",  "cenY");
        insert_uses("computeCentroid",  "y");
        insert_modifies("computeCentroid", "cenY");
        insert_uses(14, "cenY");
        insert_uses(14,  "y");
        insert_modifies(14, "cenY");
        insert_assign(17, "cenY", "cenY + y");
        insert_parent(14, 17);
        insert_follows(16, 17);

        insert_type(18, EntityType::CALL);
        //insert_call(18, "readPoint");
        insert_parent(14,18);
        insert_follows(17, 18);

        insert_type(19, EntityType::IF);
        insert_variable("count");
        insert_uses(19, "count");
        insert_uses("computeCentroid", "count");
        insert_follows(14, 19);

        insert_type(20, EntityType::ASSIGN);
        insert_variable("flag");
        insert_variable("cenX");
        insert_assign(20, "flag", "cenX");
        insert_modifies(20, "flag");
        insert_uses(20, "cenX");
        insert_modifies(19, "flag");
        insert_uses(19, "cenX");
        insert_modifies("computeCentroid", "flag");
        insert_uses("computeCentroid", "cenX");
        insert_parent(19, 20);

        insert_type(21, EntityType::ASSIGN);
        insert_variable("cenX");
        insert_variable("count");
        insert_assign(21, "cenX", "cenX / count");
        insert_uses(21, "cenX");
        insert_uses(21, "count");
        insert_modifies(21, "cenX");
        insert_uses(19, "cenX");
        insert_uses(19, "count");
        insert_modifies(19, "cenX");
        insert_uses("computeCentroid", "cenX");
        insert_uses("computeCentroid", "count");
        insert_modifies("computeCentroid", "cenX");
        insert_parent(19, 21);

        insert_type(22, EntityType::ASSIGN);
        insert_variable("cenY");
        insert_variable("count");
        insert_assign(22, "cenY", "cenY / count");
        insert_uses(22, "cenY");
        insert_uses(22, "count");
        insert_modifies(22, "cenY");
        insert_uses(19, "cenY");
        insert_uses(19, "count");
        insert_modifies(19, "cenY");
        insert_uses("computeCentroid", "cenY");
        insert_uses("computeCentroid", "count");
        insert_modifies("computeCentroid", "cenY");
        insert_parent(19, 22);
        insert_follows(21, 22);

        insert_type(23, EntityType::ASSIGN);
        insert_variable("normSq");
        insert_variable("cenX");
        insert_variable("cenY");
        insert_assign(23, "normSq", "cenX * cenX / cenY * cenY");
        insert_modifies(23, "normSq");
        insert_uses(23, "cenX");
        insert_uses(23, "cenY");
        insert_modifies("computeCentroid", "normSq");
        insert_uses("computeCentroid", "cenX");
        insert_uses("computeCentroid", "cenY");
        insert_follows(19, 23);

        extract_design();
    }
};



