// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "artifacts_xml.hxx"

// artifact_t
// 

const artifact_t::title_sequence& artifact_t::
title () const
{
  return this->title_;
}

artifact_t::title_sequence& artifact_t::
title ()
{
  return this->title_;
}

void artifact_t::
title (const title_sequence& s)
{
  this->title_ = s;
}

const artifact_t::description_sequence& artifact_t::
description () const
{
  return this->description_;
}

artifact_t::description_sequence& artifact_t::
description ()
{
  return this->description_;
}

void artifact_t::
description (const description_sequence& s)
{
  this->description_ = s;
}

const artifact_t::event_sequence& artifact_t::
event () const
{
  return this->event_;
}

artifact_t::event_sequence& artifact_t::
event ()
{
  return this->event_;
}

void artifact_t::
event (const event_sequence& s)
{
  this->event_ = s;
}

const artifact_t::id_type& artifact_t::
id () const
{
  return this->id_.get ();
}

artifact_t::id_type& artifact_t::
id ()
{
  return this->id_.get ();
}

void artifact_t::
id (const id_type& x)
{
  this->id_.set (x);
}

const artifact_t::name_type& artifact_t::
name () const
{
  return this->name_.get ();
}

artifact_t::name_type& artifact_t::
name ()
{
  return this->name_.get ();
}

void artifact_t::
name (const name_type& x)
{
  this->name_.set (x);
}

void artifact_t::
name (::std::auto_ptr< name_type > x)
{
  this->name_.set (x);
}

const artifact_t::level_type& artifact_t::
level () const
{
  return this->level_.get ();
}

artifact_t::level_type& artifact_t::
level ()
{
  return this->level_.get ();
}

void artifact_t::
level (const level_type& x)
{
  this->level_.set (x);
}

void artifact_t::
level (::std::auto_ptr< level_type > x)
{
  this->level_.set (x);
}

const artifact_t::cursed_optional& artifact_t::
cursed () const
{
  return this->cursed_;
}

artifact_t::cursed_optional& artifact_t::
cursed ()
{
  return this->cursed_;
}

void artifact_t::
cursed (const cursed_type& x)
{
  this->cursed_.set (x);
}

void artifact_t::
cursed (const cursed_optional& x)
{
  this->cursed_ = x;
}

const artifact_t::campaign_only_optional& artifact_t::
campaign_only () const
{
  return this->campaign_only_;
}

artifact_t::campaign_only_optional& artifact_t::
campaign_only ()
{
  return this->campaign_only_;
}

void artifact_t::
campaign_only (const campaign_only_type& x)
{
  this->campaign_only_.set (x);
}

void artifact_t::
campaign_only (const campaign_only_optional& x)
{
  this->campaign_only_ = x;
}


// level_t
// 

level_t::
level_t (value v)
: ::xml_schema::string (_xsd_level_t_literals_[v])
{
}

level_t::
level_t (const char* v)
: ::xml_schema::string (v)
{
}

level_t::
level_t (const ::std::string& v)
: ::xml_schema::string (v)
{
}

level_t::
level_t (const ::xml_schema::string& v)
: ::xml_schema::string (v)
{
}

level_t::
level_t (const level_t& v,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::string (v, f, c)
{
}

level_t& level_t::
operator= (value v)
{
  static_cast< ::xml_schema::string& > (*this) = 
  ::xml_schema::string (_xsd_level_t_literals_[v]);

  return *this;
}


// artifacts
// 

const artifacts::artifact_sequence& artifacts::
artifact () const
{
  return this->artifact_;
}

artifacts::artifact_sequence& artifacts::
artifact ()
{
  return this->artifact_;
}

void artifacts::
artifact (const artifact_sequence& s)
{
  this->artifact_ = s;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// artifact_t
//

artifact_t::
artifact_t (const id_type& id,
            const name_type& name,
            const level_type& level)
: ::xml_schema::type (),
  title_ (::xml_schema::flags (), this),
  description_ (::xml_schema::flags (), this),
  event_ (::xml_schema::flags (), this),
  id_ (id, ::xml_schema::flags (), this),
  name_ (name, ::xml_schema::flags (), this),
  level_ (level, ::xml_schema::flags (), this),
  cursed_ (::xml_schema::flags (), this),
  campaign_only_ (::xml_schema::flags (), this)
{
}

artifact_t::
artifact_t (const artifact_t& x,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  title_ (x.title_, f, this),
  description_ (x.description_, f, this),
  event_ (x.event_, f, this),
  id_ (x.id_, f, this),
  name_ (x.name_, f, this),
  level_ (x.level_, f, this),
  cursed_ (x.cursed_, f, this),
  campaign_only_ (x.campaign_only_, f, this)
{
}

artifact_t::
artifact_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  title_ (f, this),
  description_ (f, this),
  event_ (f, this),
  id_ (f, this),
  name_ (f, this),
  level_ (f, this),
  cursed_ (f, this),
  campaign_only_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
    this->parse (p, f);
  }
}

void artifact_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // title
    //
    if (n.name () == "title" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< title_type > r (
        title_traits::create (i, f, this));

      this->title_.push_back (r);
      continue;
    }

    // description
    //
    if (n.name () == "description" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< description_type > r (
        description_traits::create (i, f, this));

      this->description_.push_back (r);
      continue;
    }

    // event
    //
    if (n.name () == "event" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< event_type > r (
        event_traits::create (i, f, this));

      this->event_.push_back (r);
      continue;
    }

    break;
  }

  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "id" && n.namespace_ ().empty ())
    {
      this->id_.set (id_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "name" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< name_type > r (
        name_traits::create (i, f, this));

      this->name_.set (r);
      continue;
    }

    if (n.name () == "level" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< level_type > r (
        level_traits::create (i, f, this));

      this->level_.set (r);
      continue;
    }

    if (n.name () == "cursed" && n.namespace_ ().empty ())
    {
      this->cursed_.set (cursed_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "campaign_only" && n.namespace_ ().empty ())
    {
      this->campaign_only_.set (campaign_only_traits::create (i, f, this));
      continue;
    }
  }

  if (!id_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "id",
      "");
  }

  if (!name_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "name",
      "");
  }

  if (!level_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "level",
      "");
  }
}

artifact_t* artifact_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class artifact_t (*this, f, c);
}

artifact_t::
~artifact_t ()
{
}

// level_t
//

level_t::
level_t (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::string (e, f, c)
{
  _xsd_level_t_convert ();
}

level_t::
level_t (const ::xercesc::DOMAttr& a,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::string (a, f, c)
{
  _xsd_level_t_convert ();
}

level_t::
level_t (const ::std::string& s,
         const ::xercesc::DOMElement* e,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
: ::xml_schema::string (s, e, f, c)
{
  _xsd_level_t_convert ();
}

level_t* level_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class level_t (*this, f, c);
}

level_t::value level_t::
_xsd_level_t_convert () const
{
  ::xsd::cxx::tree::enum_comparator< char > c (_xsd_level_t_literals_);
  const value* i (::std::lower_bound (
                    _xsd_level_t_indexes_,
                    _xsd_level_t_indexes_ + 6,
                    *this,
                    c));

  if (i == _xsd_level_t_indexes_ + 6 || _xsd_level_t_literals_[*i] != *this)
  {
    throw ::xsd::cxx::tree::unexpected_enumerator < char > (*this);
  }

  return *i;
}

const char* const level_t::
_xsd_level_t_literals_[6] =
{
  "ultimate",
  "major",
  "minor",
  "treasure",
  "spellbook",
  "unused"
};

const level_t::value level_t::
_xsd_level_t_indexes_[6] =
{
  ::level_t::major,
  ::level_t::minor,
  ::level_t::spellbook,
  ::level_t::treasure,
  ::level_t::ultimate,
  ::level_t::unused
};

// artifacts
//

artifacts::
artifacts ()
: ::xml_schema::type (),
  artifact_ (::xml_schema::flags (), this)
{
}

artifacts::
artifacts (const artifacts& x,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  artifact_ (x.artifact_, f, this)
{
}

artifacts::
artifacts (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  artifact_ (f, this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
    this->parse (p, f);
  }
}

void artifacts::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_elements (); p.next_element ())
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // artifact
    //
    if (n.name () == "artifact" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< artifact_type > r (
        artifact_traits::create (i, f, this));

      this->artifact_.push_back (r);
      continue;
    }

    break;
  }
}

artifacts* artifacts::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class artifacts (*this, f, c);
}

artifacts::
~artifacts ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::artifacts >
artifacts_ (const ::std::string& u,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::artifacts > r (
    ::artifacts_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::artifacts >
artifacts_ (const ::std::string& u,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::artifacts > r (
    ::artifacts_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::artifacts >
artifacts_ (const ::std::string& u,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::artifacts > r (
    ::artifacts_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::artifacts >
artifacts_ (::std::istream& is,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::artifacts_ (isrc, f, p);
}

::std::auto_ptr< ::artifacts >
artifacts_ (::std::istream& is,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::artifacts_ (isrc, h, f, p);
}

::std::auto_ptr< ::artifacts >
artifacts_ (::std::istream& is,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::artifacts_ (isrc, h, f, p);
}

::std::auto_ptr< ::artifacts >
artifacts_ (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::artifacts_ (isrc, f, p);
}

::std::auto_ptr< ::artifacts >
artifacts_ (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::artifacts_ (isrc, h, f, p);
}

::std::auto_ptr< ::artifacts >
artifacts_ (::std::istream& is,
            const ::std::string& sid,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::artifacts_ (isrc, h, f, p);
}

::std::auto_ptr< ::artifacts >
artifacts_ (::xercesc::InputSource& i,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  ::std::auto_ptr< ::artifacts > r (
    ::artifacts_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::artifacts >
artifacts_ (::xercesc::InputSource& i,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::artifacts > r (
    ::artifacts_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::artifacts >
artifacts_ (::xercesc::InputSource& i,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  ::std::auto_ptr< ::artifacts > r (
    ::artifacts_ (
      d, f | ::xml_schema::flags::own_dom, p));

  return r;
}

::std::auto_ptr< ::artifacts >
artifacts_ (const ::xercesc::DOMDocument& d,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

    ::std::auto_ptr< ::artifacts > r (
      ::artifacts_ (
        c, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  const ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "artifacts" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::artifacts > r (
      ::xsd::cxx::tree::traits< ::artifacts, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "artifacts",
    "");
}

::std::auto_ptr< ::artifacts >
artifacts_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
            ::xml_schema::flags f,
            const ::xml_schema::properties&)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "artifacts" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::artifacts > r (
      ::xsd::cxx::tree::traits< ::artifacts, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "artifacts",
    "");
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

void
artifacts_ (::std::ostream& o,
            const ::artifacts& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::artifacts_ (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
artifacts_ (::std::ostream& o,
            const ::artifacts& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::artifacts_ (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
artifacts_ (::std::ostream& o,
            const ::artifacts& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::artifacts_ (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
artifacts_ (::xercesc::XMLFormatTarget& t,
            const ::artifacts& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::artifacts_ (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
artifacts_ (::xercesc::XMLFormatTarget& t,
            const ::artifacts& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::artifacts_ (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
artifacts_ (::xercesc::XMLFormatTarget& t,
            const ::artifacts& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::artifacts_ (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
artifacts_ (::xercesc::DOMDocument& d,
            const ::artifacts& s,
            ::xml_schema::flags)
{
  ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "artifacts" &&
      n.namespace_ () == "")
  {
    e << s;
  }
  else
  {
    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "artifacts",
      "");
  }
}

::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
artifacts_ (const ::artifacts& s,
            const ::xml_schema::namespace_infomap& m,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::serialize< char > (
      "artifacts",
      "",
      m, f));

  ::artifacts_ (*d, s, f);
  return d;
}

void
operator<< (::xercesc::DOMElement& e, const artifact_t& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // title
  //
  for (artifact_t::title_const_iterator
       b (i.title ().begin ()), n (i.title ().end ());
       b != n; ++b)
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "title",
        e));

    s << *b;
  }

  // description
  //
  for (artifact_t::description_const_iterator
       b (i.description ().begin ()), n (i.description ().end ());
       b != n; ++b)
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "description",
        e));

    s << *b;
  }

  // event
  //
  for (artifact_t::event_const_iterator
       b (i.event ().begin ()), n (i.event ().end ());
       b != n; ++b)
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "event",
        e));

    s << *b;
  }

  // id
  //
  {
    ::xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "id",
        e));

    a << i.id ();
  }

  // name
  //
  {
    ::xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "name",
        e));

    a << i.name ();
  }

  // level
  //
  {
    ::xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "level",
        e));

    a << i.level ();
  }

  // cursed
  //
  if (i.cursed ())
  {
    ::xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "cursed",
        e));

    a << *i.cursed ();
  }

  // campaign_only
  //
  if (i.campaign_only ())
  {
    ::xercesc::DOMAttr& a (
      ::xsd::cxx::xml::dom::create_attribute (
        "campaign_only",
        e));

    a << *i.campaign_only ();
  }
}

void
operator<< (::xercesc::DOMElement& e, const level_t& i)
{
  e << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (::xercesc::DOMAttr& a, const level_t& i)
{
  a << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (::xml_schema::list_stream& l,
            const level_t& i)
{
  l << static_cast< const ::xml_schema::string& > (i);
}

void
operator<< (::xercesc::DOMElement& e, const artifacts& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // artifact
  //
  for (artifacts::artifact_const_iterator
       b (i.artifact ().begin ()), n (i.artifact ().end ());
       b != n; ++b)
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "artifact",
        e));

    s << *b;
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

