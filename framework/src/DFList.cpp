/**********************************************************************
* Copyright (c) 2015 Mark Charlebois
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the
* disclaimer below) provided that the following conditions are met:
*
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*  * Neither the name of Dronecode Project nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
* GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
* HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
* IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*************************************************************************/
#include "DFList.hpp"

using namespace DriverFramework;

DFPointerList::DFListNode::DFListNode(void *item) :
	m_next(nullptr),
	m_item(item)
{
}

DFPointerList::DFListNode::~DFListNode()
{
}

DFPointerList::DFPointerList() :
	m_head(nullptr),
	m_end(nullptr),
	m_manage(false),
	m_size(0)
{
}

DFPointerList::DFPointerList(bool manage) :
	m_head(nullptr),
	m_end(nullptr),
	m_manage(manage),
	m_size(0)
{
}

DFPointerList::~DFPointerList()
{
	for(Index p = m_head; p != nullptr;) {
		p = p->m_next;
		if (m_manage) {
			delete(m_head->m_next);
		}
		delete(m_head);
		m_head = p;
	}
}

unsigned int DFPointerList::size()
{
	return m_size;
}

bool DFPointerList::pushBack(void *item)
{
	Index t = new DFListNode(item);
	if (t == nullptr) {
		return false;
	}
	if (m_head == nullptr) {
		m_head = t;
		m_end = t;
	} else {
		m_end->m_next = t;
		m_end = t;
	}
	++m_size;
	return true;
}

bool DFPointerList::pushFront(void *item)
{
	Index t = new DFListNode(item);
	if (t == nullptr) {
		return false;
	}
	if (m_head == nullptr) {
		m_head = t;
		m_end = t;
	} else {
		t->m_next = m_head;
		m_head = t;
	}
	++m_size;
	return true;
}

DFPointerList::Index DFPointerList::erase(Index idx)
{
	if (idx != nullptr && idx == m_head) {
		Index t = m_head->m_next;
		deleteNode(m_head);
		m_head = t;
		if (t == nullptr) {
			m_end = nullptr;
		}
		--m_size;
		return m_head;
	} else {
		for (Index p = m_head; p->m_next != nullptr;) {
			Index t = p->m_next;
			if (idx == t) {
				p->m_next = t->m_next;
				deleteNode(t);
				--m_size;
				return p->m_next;
			}
		}
	}
	return nullptr;
}

void DFPointerList::clear()
{
	while(m_head != nullptr) {
		erase(m_head);
	}
}

bool DFPointerList::empty()
{
	return (m_head == nullptr);
}

DFPointerList::Index DFPointerList::next(Index &idx)
{
	if (idx == nullptr) {
		idx = m_head;
	} else {
		idx = idx->m_next;
	}
	return idx;

}

void *DFPointerList::get(Index idx)
{
	if (idx) {
		return idx->m_item;
	}
	return nullptr;
}

	// Caller must lock before using list
	SyncObj m_sync;

void DFPointerList::deleteNode(Index node)
{
	if (m_manage) {
		delete(node->m_next);
	}
	delete(node);
}

DFUIntList::DFUIListNode::DFUIListNode(unsigned int item) :
	m_next(nullptr),
	m_item(item)
{
}

DFUIntList::DFUIListNode::~DFUIListNode()
{
}

DFUIntList::DFUIntList() :
	m_head(nullptr),
	m_end(nullptr),
	m_size(0)
{
}

DFUIntList::~DFUIntList()
{
	for(Index p = m_head; p != nullptr;) {
		p = p->m_next;
		delete(m_head);
		m_head = p;
	}
}

unsigned int DFUIntList::size()
{
	return m_size;
}

bool DFUIntList::pushBack(unsigned int item)
{
	Index t = new DFUIListNode(item);
	if (t == nullptr) {
		return false;
	}
	if (m_head == nullptr) {
		m_head = t;
		m_end = t;
	} else {
		m_end->m_next = t;
		m_end = t;
	}
	++m_size;
	return true;
}

bool DFUIntList::pushFront(unsigned int item)
{
	Index t = new DFUIListNode(item);
	if (t == nullptr) {
		return false;
	}
	if (m_head == nullptr) {
		m_head = t;
		m_end = t;
	} else {
		t->m_next = m_head;
		m_head = t;
	}
	++m_size;
	return true;
}

DFUIntList::Index DFUIntList::erase(Index idx)
{
	if (idx != nullptr && idx == m_head) {
		Index t = m_head->m_next;
		delete(m_head);
		m_head = t;
		if (t == nullptr) {
			m_end = nullptr;
		}
		--m_size;
		return m_head;
	} else {
		for (Index p = m_head; p->m_next != nullptr;) {
			Index t = p->m_next;
			if (idx == t) {
				p->m_next = t->m_next;
				delete(t);
				--m_size;
				return p->m_next;
			}
		}
	}
	return nullptr;
}

void DFUIntList::clear()
{
	while(m_head != nullptr) {
		erase(m_head);
	}
}

bool DFUIntList::empty()
{
	return (m_head == nullptr);
}

DFUIntList::Index DFUIntList::next(Index &idx)
{
	if (idx == nullptr) {
		idx = m_head;
	} else {
		idx = idx->m_next;
	}
	return idx;
}

bool DFUIntList::get(Index idx, unsigned int &val)
{
	if (idx) {
		val = idx->m_item;
		return true;
	}
	return false;
}
