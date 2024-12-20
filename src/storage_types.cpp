#include "storage_types.hpp"

Package PackageQueue::pop(){
    Package package;
    if(this -> package_queue_type_ == PackageQueueType::FIFO){
        package = std::move(this -> package_list_.front());
        this -> package_list_.pop_front();
    } else{
        package = std::move(this -> package_list_.back());
        this -> package_list_.pop_back();
    }
    return package;
}
