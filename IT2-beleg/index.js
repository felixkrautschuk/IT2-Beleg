function start() 
{
    if (document.getElementById("reusableForm") != null) {
        node.parentNode.removeChild(document.getElementById("reusableForm"));
    }
    node = document.getElementById("matrix");
    node.parentNode.insertBefore(createTable(document.getElementById("anzahlGleichungen").value,                                document.getElementById("anzahlUnbekannte").value), node );
//    node.parentNode.insertAdjacentHTML('','');
} 

function createTable(row, col, id) 
{
    var form = document.createElement("form");
    var formid = document.createAttribute("id");
    formid.value = "reusableForm";
    form.setAttributeNode(formid);
    var action = document.createAttribute("action");
    action.value = "gauss.cgi"
    form.setAttributeNode(action);
    
    // EKELHAFT(BEFEHL)
    var rowP = document.createElement("input");
    var name = document.createAttribute("name");
    name.value = "row";
    rowP.setAttributeNode(name);
    rowP.value = "" + row;
    var style1 = document.createAttribute("style");
    style1.value = "display: none;";
    rowP.setAttributeNode(style1);
    var colP = document.createElement("input");
    var name2 = document.createAttribute("name");
    name2.value = "col";
    colP.setAttributeNode(name2);
    colP.value = "" + col;
    var style2 = document.createAttribute("style");
    style2.value = "display: none;";
    colP.setAttributeNode(style2);
    
    form.appendChild(rowP);
    form.appendChild(colP);

    var myTable     = document.createElement("table");
    var mytablebody = document.createElement("tbody");


    for(var j = 0; j < row; j++) 
    {
        var mycurrent_row = document.createElement("tr");
        for(var i = 0; i < col; i++) 
        {
            mycurrent_cell = document.createElement("td");  
            var newTextfield = document.createElement("input");
            newTextfield.value = "3";
            var atts = document.createAttribute("id");
            atts.value = j + "-" + i;
            var name = document.createAttribute("name");
            name.value = "var" + atts.value;
            newTextfield.setAttributeNode(atts);
            newTextfield.setAttributeNode(name);
            mycurrent_cell.appendChild(newTextfield);
            mycurrent_row.appendChild(mycurrent_cell);
        }
        mytablebody.appendChild(mycurrent_row);
    }
    myTable.appendChild(mytablebody);
    //myTable.setAttribute("ID", id);
    form.appendChild(myTable);
    var submitButton = document.createElement("input");
    var type = document.createAttribute("type");
    type.value = "submit";
    var subText = document.createAttribute("value");
    subText.value = "Los gehts!";
    submitButton.setAttributeNode(type);
    submitButton.setAttributeNode(subText);
    form.appendChild(submitButton);
    return form;
}
