//
// Created by Marek Generowicz on 16/12/2024.
//

#ifndef PROJEKT_NODES_HPP
#define PROJEKT_NODES_HPP
#include "storage_types.hpp" //w tym jest storage_types_package oraz types
#include "helpers.hpp"
#include <map>
#include <optional>
#include <memory>


class IPackageReceiver{
public:
    virtual ~IPackageReceiver() = default;

    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;

    virtual void receive_package(Package&& p) = 0;

    virtual ElementID get_id() const = 0;
};

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences()
            : generate_probability_([]() { return 0.0; }) {} // Domyślny generator zwraca 0.0

    ReceiverPreferences(ProbabilityGenerator pg)
            : generate_probability_(std::move(pg)) {}


    const_iterator begin() const {return preferences_.cbegin(); }
    const_iterator end() const {return preferences_.cend(); }
    const_iterator cbegin() const {return preferences_.cbegin(); }
    const_iterator cend() const {return preferences_.cend();}

    void add_receiver(IPackageReceiver* r);

    void remove_receiver(IPackageReceiver* r);

    IPackageReceiver* choose_receiver();

    preferences_t& get_preferences(){ return this -> preferences_;}

private:
    preferences_t preferences_;
    ProbabilityGenerator generate_probability_;
};

class PackageSender{
public:
    PackageSender() = default;
    PackageSender(PackageSender&& movable) = default;

    void send_package();

    const std::optional<Package>& get_sending_buffer() const {return buffer_;};

    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&& p) { buffer_.emplace(p.get_id()); };

    std::optional<Package> buffer_ = std::nullopt;
};


class Ramp : public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : PackageSender(), ID_(id), DI_(di), T_(), buffer_() {};

    ElementID get_element() { return ID_;}

    TimeOffset get_delivery_interval() {return DI_;}

    void deliver_goods(Time t);
private:
    ElementID ID_;
    TimeOffset DI_;
    Time T_;
    std::optional<Package> buffer_;
};

class Worker : public IPackageReceiver, PackageSender{
public:
    Worker(ElementID id, TimeOffset di, std::unique_ptr<IPackageQueue> q) : ID_(id), DI_(di), Q_(std::move(q)) {};

    IPackageStockpile::const_iterator begin() const override {return Q_ -> cbegin();}
    IPackageStockpile::const_iterator end() const override {return Q_ -> cend();}
    IPackageStockpile::const_iterator cbegin() const override {return Q_ -> cbegin();}
    IPackageStockpile::const_iterator cend() const override {return Q_ -> cend();}

    void receive_package(Package&& p) override{
        Q_ -> push(std::move(p));
    }

    ElementID get_id() const override{
        return this -> ID_;
    }

    const std::optional<Package>& get_sending_buffer() const{
        return buffer_;
    }


    void do_work(Time t);

    TimeOffset get_processing_duration() const{
        return this -> DI_;
    }

    Time get_package_processing_start_time() const{
        return this -> T_;
    }
private:
    ElementID ID_;
    TimeOffset DI_;
    Time T_;
    std::unique_ptr<IPackageQueue> Q_;
    std::optional<Package> buffer_ = std::nullopt;
};

class Storehouse : public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)) : ID_(id), D_(std::move(d)) {};

    IPackageStockpile::const_iterator begin() const override {return D_ -> cbegin();}
    IPackageStockpile::const_iterator end() const override {return D_ -> cend();}
    IPackageStockpile::const_iterator cbegin() const override {return D_ -> cbegin();}
    IPackageStockpile::const_iterator cend() const override {return D_ -> cend();}

    void receive_package(Package&& p) override{
        D_ -> push(std::move(p));
    }

    ElementID get_id() const override {return this -> ID_;}
private:
    ElementID ID_;
    std::unique_ptr<IPackageStockpile> D_;
};

#endif //PROJEKT_NODES_HPP
//klasy ujęte na diagramie UML w pakiecie Nodes
//typ wyliczeniowy ReceiverType
//klasy IPackageReceiver, Storehouse, ReceiverPreferences, PackageSender, Ramp, Worker
