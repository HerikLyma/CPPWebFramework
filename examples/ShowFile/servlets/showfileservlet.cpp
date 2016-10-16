/**
  @file showfileservlet.h
  @author Herik Lima
*/

#include "showfileservlet.h"

void ShowFileServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    Q_UNUSED(response)
    request.getRequestDispatcher("/pages/showfile").forward(request, response);
}

void ShowFileServlet::doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    auto files(std::move(request.getUploadedFiles()));
    if(files.size())
    {
        for(auto it = files.begin(); it != files.end(); ++it)
        {
            QString fileName = it.key();
            QString extention = CWF::FileManager().fileExtention(fileName);
            extention = extention.toLower();
            if(extention == "png" || extention == "gif" || extention == "bmp")
                response.addHeader("Content-Type", ("image/" + extention.toLatin1()));
            else if(extention == "jpe" || extention == "jpg")
                response.addHeader("Content-Type", "image/jpeg");

            response.addHeader("content-disposition", ("inline; filename=" + fileName.toLatin1()));
            response.write(it.value());
            break;
        }
    }
    else
    {
        response.write("<html><head><title>Falha</title></head><body><center><font color=\"red\" size = \"6\">Nenhum arquivo salvo.\n</font></center></body></html>");
    }
}
