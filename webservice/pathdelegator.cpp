#include "pathdelegator.h"

PathDelegator::PathDelegator(QObject *parent) :
    HttpRequestHandler(parent)
{
}

void PathDelegator::service(HttpRequest &request, HttpResponse &response) {
    QByteArray path = request.getPath();
    if (paths.contains(path)) {
        paths[path]->service(request, response);
    }
    else {
        response.setStatus(404, QByteArray("Cannot find ") + path);
        response.write(QByteArray("Cannot find ") + path);
    }
}

void PathDelegator::addPath(const QByteArray &path, HttpRequestHandler *handler) {
    paths.insert(path, handler);
}
