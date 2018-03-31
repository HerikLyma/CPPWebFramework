#ifndef HELLOCONTROLLER_H
#define HELLOCONTROLLER_H

#include <cwf/httpservlet.h>
#include <model/hellomodel.h>

class HelloController : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override
    {
        HelloModel model;
        request.addAttribute("model", &model);
        request.getRequestDispatcher("/pages/helloview.xhtml").forward(request, response);
    }
};

#endif // HELLOCONTROLLER_H
