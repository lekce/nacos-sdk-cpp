#include <iostream>
#include <list>
#include "factory/NacosServiceFactory.h"
#include "naming/Instance.h"
#include "NacosString.h"
#include "Properties.h"
#include "constant/PropertyKeyConst.h"
#include "ResourceGuard.h"

using namespace std;
using namespace nacos;

int main() {
    Properties configProps;
    configProps[PropertyKeyConst::SERVER_ADDR] = "127.0.0.1";
    NacosServiceFactory *factory = new NacosServiceFactory(configProps);
    ResourceGuard <NacosServiceFactory> _guardFactory(factory);
    NamingService *namingSvc = factory->CreateNamingService();
    ResourceGuard <NamingService> _guardService(namingSvc);

    list <Instance> instances = namingSvc->getAllInstances("TestNamingService1");
    cout << "getAllInstances from server:" << endl;
    for (list<Instance>::iterator it = instances.begin();
         it != instances.end(); it++) {
        cout << "Instance:" << it->toString() << endl;
    }

    return 0;
}
