/*
    Copyright (C) 2019 Joshua Wade

    This file is part of Anthem.

    Anthem is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    Anthem is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Anthem. If not, see
                        <https://www.gnu.org/licenses/>.
*/

#include "project.h"

#include "Utilities/exceptions.h"

Project::Project(Communicator* parent, IdGenerator* id) : ModelItem(parent, "project") {
    this->id = id;
    transport = new Transport(this, id);
}

Project::Project(Communicator* parent, IdGenerator* id, rapidjson::Value& projectVal) : ModelItem(parent, "project") {
    this->id = id;
    transport = new Transport(this, id, projectVal["transport"]);
}

void Project::externalUpdate(QStringRef pointer, PatchFragment& patch) {
    QString transportStr = "/transport";
    if (pointer.startsWith(transportStr)) {
        transport->externalUpdate(pointer.mid(transportStr.length()), patch);
    }
}

void Project::serialize(rapidjson::Value& value, rapidjson::Document& doc) {
    value.SetObject();

    rapidjson::Value transportValue;
    transport->serialize(transportValue, doc);
    value.AddMember("transport", transportValue, doc.GetAllocator());
}
