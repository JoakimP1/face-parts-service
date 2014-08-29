#include "pathdelegator.h"

PathDelegator::PathDelegator(QObject *parent) :
    HttpRequestHandler(parent) {
}

PathDelegator::~PathDelegator() {
    for (QMap<QByteArray, HttpRequestHandler*>::iterator iter = paths.begin(); iter != paths.end(); ++iter) {
        if (iter.value()) {
            delete iter.value();
        }
    }
}

void PathDelegator::service(HttpRequest &request, HttpResponse &response) {
    QByteArray path = request.getPath();
    if (path.contains(".")) {
        path = path.left(path.indexOf("."));
    }
    if (paths.contains(path)) {
        paths[path]->service(request, response);
    }
    else {
        response.setStatus(404, QByteArray("Cannot find ") + path);
    }
}

void PathDelegator::addPath(const QByteArray &path, HttpRequestHandler *handler) {
    paths.insert(path, handler);
}
