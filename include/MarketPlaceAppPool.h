/* -------------------------------------------------------------------------- */
/* Copyright 2002-2015, OpenNebula Project, OpenNebula Systems                */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License"); you may    */
/* not use this file except in compliance with the License. You may obtain    */
/* a copy of the License at                                                   */
/*                                                                            */
/* http://www.apache.org/licenses/LICENSE-2.0                                 */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/* -------------------------------------------------------------------------- */

#ifndef MARKETPLACEAPP_POOL_H_
#define MARKETPLACEAPP_POOL_H_

#include "MarketPlaceApp.h"

class SqlDB;

class MarketPlaceAppPool : public PoolSQL
{
public:
    MarketPlaceAppPool(SqlDB * db):PoolSQL(db,MarketPlaceApp::table,true,true){};

    ~MarketPlaceAppPool(){};

    /* ---------------------------------------------------------------------- */
    /* Methods for DB management                                              */
    /* ---------------------------------------------------------------------- */

    /**
     *  Allocates a new MarketPlaceApp, writing it in the pool database.
     *    @param uid the user id of the MarketPlace owner
     *    @param gid the id of the group this object is assigned to
     *    @param uname name of the user
     *    @param gname name of the group
     *    @param umask permissions umask
     *    @param apptemplate MarketPlaceApp definition template
     *    @param mp_id of the MarketPlace to store de App
     *    @param mp_name of the MarketPlace
     *    @param mp_data XML representation of the target MarketPlace
     *    @param oid the id assigned to the MarketPlace
     *    @param error_str Returns the error reason, if any
     *
     *    @return the oid assigned to the object, -1 in case of failure
     */
    int allocate(
            int                uid,
            int                gid,
            const std::string& uname,
            const std::string& gname,
            int                umask,
            MarketPlaceAppTemplate * apptemplate,
            int                mp_id,
            const std::string& mp_name,
            const std::string& mp_data,
            int *              oid,
            std::string&       error_str);
    /**
     *  Imports an app into the marketplace, as reported by the monitor driver
     *    @param template to generate app with the from_template64 function
     *    @param mp_id of the MarketPlace to store de App
     *    @param mp_name of the MarketPlace
     *    @param error_str Returns the error reason, if any
     *
     *    @return the oid assigned to the object, -1 in case of failure, -2
     *    already imported
     */
    int import(const std::string& t64, int mp_id, const std::string& mp_name,
            std::string& error_str);

    /**
     *  Function to get a MarketPlaceApp from the pool
     *    @param oid MarketPlaceApp unique id
     *    @param lock locks the MarketPlaceApp mutex
     *    @return a pointer to the MarketPlaceApp, 0 if not loaded
     */
    MarketPlaceApp * get(int oid, bool lock)
    {
        return static_cast<MarketPlaceApp *>(PoolSQL::get(oid,lock));
    };

    /**
     *  Gets an object from the pool (if needed the object is loaded from the
     *  database).
     *   @param name of the object
     *   @param uid id of owner
     *   @param lock locks the object if true
     *
     *   @return a pointer to the object, 0 in case of failure
     */
    MarketPlaceApp * get(const std::string& name, int uid, bool lock)
    {
        return static_cast<MarketPlaceApp *>(PoolSQL::get(name, uid, lock));
    };

    /**
     *  Bootstraps the database table(s) associated to the MarketPlace pool
     *    @return 0 on success
     */
    static int bootstrap(SqlDB * _db)
    {
        return MarketPlaceApp::bootstrap(_db);
    };

    /**
     *  Dumps the MarketPlace pool in XML format. A filter can be also added to
     *  the query
     *  @param oss the output stream to dump the pool contents
     *  @param where filter for the objects, defaults to all
     *  @param limit parameters used for pagination
     *
     *  @return 0 on success
     */
    int dump(std::ostringstream& oss, const std::string& where,
		const std::string& limit)
    {
        return PoolSQL::dump(oss, "MARKETPLACEAPP_POOL", MarketPlaceApp::table,
                where, limit);
    };

    /** Update a particular MarketPlaceApp
     *    @param zone pointer to Zone
     *    @return 0 on success
     */
    int update(PoolObjectSQL * objsql);

private:

    /**
     *  Factory method to produce objects
     *    @return a pointer to the new object
     */
    PoolObjectSQL * create()
    {
        return new MarketPlaceApp(-1,-1,"","", 0, 0);
    };
};

#endif /*MARKETPLACE_POOL_H_*/