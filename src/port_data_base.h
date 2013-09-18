/* 
 * File:   port_data_base.h
 * Author: kirill
 *
 * Created on August 23, 2013, 10:33 AM
 */

#ifndef PORT_DATA_BASE_H
#define	PORT_DATA_BASE_H

#include <flowvr/module.h>
#include <boost/serialization/vector.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <sstream>

namespace flowvr
{
  template < typename data >
  flowvr::MessageWrite * create_message(flowvr::ModuleAPI * flowvr_api, const data &source)
  {
    using namespace std;
    flowvr::MessageWrite * result = new flowvr::MessageWrite();

    ostringstream ss(stringstream::out | stringstream::binary);
    boost::archive::binary_oarchive oa(ss);

    oa << source;

    result->data = flowvr_api->alloc(ss.str().length());

    memcpy(result->data.writeAccess(), ss.str().data(), ss.str().length());

    return result;
  }

  template < typename data >
  void parse_message(flowvr::Message &m, data &out )
  {
    using namespace std;

    string a;

    a.assign(m.data.readAccess(), m.data.readAccess() + m.data.getSize());

    istringstream ss(a, stringstream::in | stringstream::binary);

    boost::archive::binary_iarchive ia(ss);

    ia >> out;
  }
}

#endif	/* PORT_DATA_BASE_H */

