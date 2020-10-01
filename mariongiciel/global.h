#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>

namespace mariongiciel::global {

#ifdef QT_DEBUG
     const QString _APP_LOCATION_ = "D:/Qt programmation/mariongiciel/";
#else
    const QString _APP_LOCATION_ = "";
#endif

    namespace info {
        const QString _INFO_VERSION_ = "0.1";
        const QString _INFO_VERSION_STATUS_ = "ALPHA";
    } // END NAMESPACE info

    namespace rcs {
        const QString _LOCATION_ = _APP_LOCATION_ + "rcs/";

        namespace account {
             const QString _LOCATION_ = rcs::_LOCATION_ + "account/";
             const QString _ACCOUNT_ = _LOCATION_ + "account";
             const QString _COMPRESS_FORMAT_ = ".mg";
             const QString _DEFAULT_FORMAT_ = ".json";
        } // END NAMESPACE account

        namespace icon {
            const QString _LOCATION_ = rcs::_LOCATION_+"icon/";
            const QString _ACCOUNT_ = _LOCATION_ + "account_512.png";
            const QString _SEARCH_ = _LOCATION_ + "search_512.png";
            const QString _POLE_ = _LOCATION_ + "pole.png";
            const QString _MAPS_ = _LOCATION_ + "maps.png";
            const QString _API_ = _LOCATION_ + "api.png";
            const QString _LOADING_ = _LOCATION_ + "loading_512.png";
            const QString _REMOVE_ = _LOCATION_ + "remove_512.png";
            const QString _DOWNLOAD_ = _LOCATION_ + "download_512.png";
            const QString _ACTION_ = _LOCATION_ + "action_512.png";

        } // END NAMESPACE icon

        namespace css {
            const QString _LOCATION_ = rcs::_LOCATION_+"css/";
            const QString _STYLE_ = _LOCATION_ + "style.css";
        } // END NAMESPACE css

        namespace data {
            const QString _LOCATION_ = rcs::_LOCATION_ + "data/";
        } // END NAMESPACE data

        namespace referencial {
            const QString _LOCATION_ = rcs::_LOCATION_ + "referencial/";
        } // END NAMESPACE referencial

        namespace log {
            const QString _LOCATION_ = rcs::_LOCATION_ + "log/";
        } // END NAMESPACE log

        namespace archive {
            const QString _LOCATION_ = rcs::_LOCATION_ + "archive/";
        } // END NAMESPACE archive

        namespace config {
            const QString _LOCATION_ = rcs::_LOCATION_ +"/config";
        } // END NAMESPACE config

    } // END NAMESPACE rcs

} // END NAMESPACE global

#endif // GLOBAL_H
