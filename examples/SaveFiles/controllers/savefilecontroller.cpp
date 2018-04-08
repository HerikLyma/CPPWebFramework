/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "savefilescontroller.h"

void SaveFilesController::doGet(CWF::Request &request, CWF::Response &response) const
{
    Q_UNUSED(response)
    request.getRequestDispatcher("/pages/savefiles.html").forward(request, response);
}

void SaveFilesController::doPost(CWF::Request &request, CWF::Response &response) const
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
