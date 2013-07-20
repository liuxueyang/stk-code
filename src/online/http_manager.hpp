//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2013 Glenn De Jonghe
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HTTP_MANAGER_HPP
#define HTTP_MANAGER_HPP

#include <string>
#include <curl/curl.h>
#include <irrString.h>
#include <queue>
#include <pthread.h>

#ifdef WIN32
#  include <winsock2.h>
#endif

#include "io/xml_node.hpp"
#include "utils/string_utils.hpp"
#include "utils/synchronised.hpp"
#include "online/request.hpp"

namespace Online{

    /**
      * \brief Class to connect with a server over HTTP
      * \ingroup online
      */
    class HTTPManager
    {
        protected:

            /** The current requested being worked on. */
            Online::Request *         m_current_request;

            /** A conditional variable to wake up the main loop. */
            pthread_cond_t            m_cond_request;

            /** Signal an abort in case that a download is still happening. */
            Synchronised<bool>        m_abort;

            /** Thread id of the thread running in this object. */
            Synchronised<pthread_t *> m_thread_id;

            /** The list of pointes to all requests. */
            Synchronised< std::priority_queue <
                                                Online::Request*,
                                                std::vector<Online::Request*>,
                                                Online::Request::Compare
                                               >
                        >  m_request_queue;

            static void  *mainLoop(void *obj);
            void startNetworkThread();

            HTTPManager(); //const std::string &url
            ~HTTPManager();

        public:

            // singleton
            static HTTPManager* get();
            static void deallocate();
            static bool isRunning();

            //Execute
            std::string getPage(Online::Request * request);
            XMLNode * getXMLFromPage(Online::Request * request);

            void addRequest(Online::Request *request);
            void cancelAllDownloads();
            void stopNetworkThread();

            bool getAbort(){ return m_abort.getAtomic(); };

    }; //class HTTPManager
} // namespace Online

#endif // HTTP_MANAGER_HPP

/*EOF*/
