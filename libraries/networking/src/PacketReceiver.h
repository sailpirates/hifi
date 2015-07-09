//
//  PacketReceiver.h
//  libraries/networking/src
//
//  Created by Stephen Birarda on 1/23/2014.
//  Update by Ryan Huffman on 7/8/2015.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_PacketReceiver_h
#define hifi_PacketReceiver_h

#include <QtCore/QObject>

class PacketReceiver : public QObject {
    Q_OBJECT
public:
    PacketReceiver(QObject* parent = 0);
    
    int getInPacketCount() const { return _inPacketCount; }
    int getOutPacketCount() const { return _outPacketCount; }
    int getInByteCount() const { return _inByteCount; }
    int getOutByteCount() const { return _outByteCount; }
    
    void resetCounters() { _inPacketCount = 0; _outPacketCount = 0; _inByteCount = 0; _outByteCount = 0; }

    void shutdown() { _isShuttingDown = true; }

    void registerPacketListener(PacketType::Value type, QObject* object, QString methodName);

public slots:
    void processDatagrams();
    
private:
    QMutex packetListenerLock;
    QMap<PacketType::Value, QPair<QObject*, QString>> packetListenerMap;
    int _inPacketCount = 0;
    int _outPacketCount = 0;
    int _inByteCount = 0;
    int _outByteCount = 0;
    bool _isShuttingDown = false;
};

#endif // hifi_PacketReceiver_h
