#include "types.hpp"
#include <set>
//klasa Package
class Package {
public:
    Package();

    Package(ElementID ID) : ID_(ID) {assigned_IDs.insert(ID_);}

    Package(Package&& package) : ID_(package.ID_) {}

    ElementID get_id() const {return ID_;}

    Package& operator=(Package&& package);

    ~Package();
private:
    ElementID ID_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};
