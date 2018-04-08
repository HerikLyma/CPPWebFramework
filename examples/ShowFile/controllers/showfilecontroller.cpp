/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "showfilecontroller.h"

void ShowFileController::doGet(CWF::Request &request, CWF::Response &response) const
{
    Q_UNUSED(response)
    request.getRequestDispatcher("/pages/showfile.html").forward(request, response);
}

void ShowFileController::doPost(CWF::Request &request, CWF::Response &response) const
{
    auto files(std::move(request.getUploadedFiles()));
    if(files.size())
    {
        for(auto it = files.begin(); it != files.end(); ++it)
        {
            QString fileName = it.key();
            QString extention = CWF::FileManager().fileExtention(fileName).toLower();

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
        QByteArray text;
        text  = "<html>";
        text +=     "<head>";
        text +=         "<title>";
        text +=             "Failure";
        text +=         "</title>";
        text +=     "</head>";
        text +=     "<body>";
        text +=         "<center>";
        text +=             "<font color=\"red\" size = \"6\">";
        text +=                 "Error.";
        text +=             "</font>";
        text +=         "</center>";
        text +=     "</body>";
        text += "</html>";
        response.write(text);
    }
}
