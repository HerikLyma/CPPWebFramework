/**
  @file savefilesservlet.cpp
  @author Herik Lima
*/

#include "savefilesservlet.h"

void SaveFilesServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    Q_UNUSED(response)
    request.getRequestDispatcher("/pages/savefiles").forward(request, response);
}

void SaveFilesServlet::doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    QByteArray html(std::move("<html><head><title>Success</title></head><body><center><font color=\"red\" size = \"6\">"));
    auto files(std::move(request.getUploadedFiles()));
    if(files.size())
    {
        for(auto it = files.begin(); it != files.end(); ++it)
        {
            //The files will be save here, change it.
            QFile file("/home/herik/" + it.key());
            file.open(QIODevice::WriteOnly);
            file.write(it.value());
            file.close();
        }
        html += QByteArray::number(files.size()) + " Saved files.\n";
    }
    else
    {
        html.replace("Success", "Failure");
        html += "None saved file.\n";
    }
    html += "</font></center></body></html>";
    response.write(html);
}
