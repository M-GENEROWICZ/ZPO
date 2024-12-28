#include "nodes.hpp"

#include <iostream>
using ReceiverPair = std::pair<IPackageReceiver* const, double>;

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    auto preferences_size = preferences_.size();
    if (preferences_size == 0){
        preferences_[r] = 1.;
    }else{
        auto denominator = static_cast<double>(preferences_size + 1);
        std::for_each(preferences_.begin(), preferences_.end(), [=](ReceiverPair& receiver) {
            receiver.second = 1 / denominator;
        });
        preferences_[r] = 1. / denominator;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    auto receiver_to_remove = preferences_.find(r);
    if (receiver_to_remove == preferences_.end()) return;

    preferences_.erase(receiver_to_remove);

    auto num_of_receivers = preferences_.size();
    if (num_of_receivers == 0) return;

    std::for_each(preferences_.begin(), preferences_.end(), [=](ReceiverPair& receiver) {
        receiver.second = 1. / static_cast<double>(num_of_receivers);
    });
}

IPackageReceiver* ReceiverPreferences::choose_receiver(){
    auto prob = generate_probability_();
    std::cerr << "Generated probability: " << prob << std::endl;
    if(prob > 0 && prob <= 1){
        double distribution = 0.0;
        for (auto &rec: preferences_) {
            distribution = distribution + rec.second;
            std::cerr << "Receiver ID: " << rec.first->get_id() << ", Distribution: " << distribution << std::endl;
            if (distribution < 0 || distribution > 1) {
                return nullptr;
            }
            if (prob <= distribution) {
                return rec.first;
            }
        }
    }
    std::cerr << "No receiver chosen." << std::endl;
    return nullptr;
}

void PackageSender::send_package() {
    if(!buffer_.has_value()) {
        std::cerr << "Buffer is empty, nothing to send." << std::endl;
        return;
    }
    IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
    if (receiver != nullptr) {
        std::cerr << "Sending package to receiver with ID: " << receiver->get_id() << std::endl;
        receiver->receive_package(std::move(*buffer_));
        buffer_.reset();
    } else {
        std::cerr << "No valid receiver found." << std::endl;
    }
}

void Ramp::deliver_goods(Time t) {
    if (!buffer_) {
        push_package(Package());
        buffer_.emplace(ID_);
        T_ = t;
    } else if (t - DI_ == T_) {
        push_package(Package());
    }
}

void Worker::do_work(Time t) {
    if (!buffer_) {
        push_package(Package());
        buffer_.emplace(ID_);
        T_ = t;
    } else if (t - DI_ == T_) {
        push_package(Package());
        buffer_.reset();
    }
}

