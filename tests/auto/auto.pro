TEMPLATE = subdirs
SUBDIRS += cmake \
    qknxadditionalinfo \
    qknxaddress \
    qknxnetipconfigdib \
    qknxnetipconnectionheader \
    qknxnetipconnectionstaterequest \
    qknxnetipconnectionstateresponse \
    qknxnetipconnectrequest \
    qknxnetipconnectresponse \
    qknxnetipcrd \
    qknxnetipcri \
    qknxnetipcurrentconfigdib \
    qknxnetipdescriptionrequest \
    qknxnetipdescriptionresponse \
    qknxnetipdeviceconfigurationacknowledge \
    qknxnetipdeviceconfigurationrequest \
    qknxnetipdevicedib \
    qknxnetipdisconnectrequest \
    qknxnetipdisconnectresponse \
    qknxnetiphpai \
    qknxnetipknxaddressesdib \
    qknxnetipmanufacturerdib \
    qknxnetiproutingbusy \
    qknxnetiproutingindication \
    qknxnetiproutinglostmessage \
    qknxnetipsearchrequest \
    qknxnetipsearchresponse \
    qknxnetipservicefamiliesdib \
    qknxnetipstructure \
    qknxnetiptunnelingacknowledge \
    qknxnetiptunnelingrequest \
    qknxtunnelframe \
    qknxtpdufactory \
    qknxdevicemanagementframe \
    qknxcontrolfield \
    qknxtunnelframefactory \
    qknxdatapointtype \
    qknxproject \
    qknxgroupaddressinfo \
    qknxbytearray \
    qknxnetiptunnelingfeature \
    qknxnetiptunnelinginfodib \
    qknxnetipextendeddevicedib \
    qknxnetiproutingsystembroadcast \
    qknxnetipsecuredservicefamiliesdib \
    qknxnetipsessionrequest \
    qknxnetipsessionresponse \
    qknxnetiprouter

QT_FOR_CONFIG += network
qtConfig(opensslv11):SUBDIRS+=qknxcryptographicengine
