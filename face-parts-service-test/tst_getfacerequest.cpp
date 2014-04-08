#include "tst_getfacerequest.h"
#include <QString>
#include <QtTest>
#include <webservice/getfacerequest.h>

void GetFaceRequestTest::initTestCase() {
    facemodel_t* faceModel = facemodel_readFromFile("../resources/face_p146.xml");
    posemodel_t* poseModel = posemodel_readFromFile("../resourcess/pose_BUFFY.xml");
    faceRequest = new GetFaceRequest(faceModel, poseModel);
}

void GetFaceRequestTest::cleanupTestCase() {
    delete faceRequest;
}

void GetFaceRequestTest::badFile()
{
    QSettings settings;
    HttpRequest request(&settings);
    HttpResponse response(NULL);

    faceRequest->service(request, response);

    QCOMPARE(500, response.getStatus());
}

void GetFaceRequestTest::noFace() {
    QTemporaryFile* file = QTemporaryFile::createLocalFile("images/48170621_4.jpg");
    QJsonDocument doc = faceRequest->getJSONFaces(file);
    QJsonDocument emptyDoc;

    QCOMPARE(emptyDoc, doc);
    delete file;
}

void GetFaceRequestTest::goodFace() {
    QTemporaryFile* file = QTemporaryFile::createLocalFile("images/1.jpg");
    QJsonDocument doc = faceRequest->getJSONFaces(file);
    QJsonDocument emptyDoc;

    QCOMPARE(emptyDoc, doc);
    delete file;
}

void GetFaceRequestTest::profile() {
    QTemporaryFile* file = QTemporaryFile::createLocalFile("images/profile.jpg");
    QJsonDocument doc = faceRequest->getJSONFaces(file);
    QJsonDocument emptyDoc;

    QCOMPARE(emptyDoc, doc);
    delete file;
}

void GetFaceRequestTest::faceFromPose() {
    QTemporaryFile* file = QTemporaryFile::createLocalFile("images/10009091_3.jpg");
    QJsonDocument doc = faceRequest->getJSONFaces(file);
    QJsonDocument emptyDoc;

    QCOMPARE(emptyDoc, doc);
    delete file;
}
