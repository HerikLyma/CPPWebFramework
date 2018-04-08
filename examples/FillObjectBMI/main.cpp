/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/cppwebapplication.h>
#include <model/usermodel.h>

class BmiController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        request.getRequestDispatcher("/pages/bmi.html").forward(request, response);
    }

    void doPost(CWF::Request &request, CWF::Response &response) const override
    {
        UserModel model;
        request.fillQObject(&model);
        request.addAttribute("model", &model);
        request.getRequestDispatcher("/pages/bmiresults.view").forward(request, response);
    }
};


int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/FillObjectBMI/server/");
    server.addUrlController<BmiController>("/bmi");
    return server.start();
}
