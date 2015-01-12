var MAX_LENGTH = 14;

function start() 
{
    var anzGleichungen = document.getElementById("anzahlGleichungen").value;
    var anzVariablen = document.getElementById("anzahlUnbekannte").value;
    
    if ( anzGleichungen <= 0 || anzGleichungen > MAX_LENGTH || anzVariablen <= 0 || anzVariablen > MAX_LENGTH) {
        alert("Bitte nur Zahlen zwischen 1 und " + MAX_LENGTH + " eingeben!");
        return;
    }
    
    anzVariablen++;
    
    if (document.getElementById("reusableForm") != null) {
        node.removeChild(document.getElementById("reusableForm"));
    }
    node = document.getElementById("platzhalter");
//    node.parentNode.insertBefore(createTable(anzGleichungen, anzVariablen) );
    node.appendChild(createTable(anzGleichungen, anzVariablen));
} 



function createTable(row, col) 
{
    var form = document.createElement("form");
    var formid = document.createAttribute("id");
    formid.value = "reusableForm";
    form.setAttributeNode(formid);
    var action = document.createAttribute("action");
    action.value = "./gauss.cgi";
    form.setAttributeNode(action);
    
    form.onsubmit = function()
    {
        for(var j = 0; j < row; j++) 
        {
            for(var i = 0; i < col; i++) 
            {
                if ( document.getElementById(j + "-" + i).value == "" ) 
                {
                    alert("Folgendes Matrizenelement ist leer: \nGleichung: " + (j+1) + " Feld: " + (i+1));
                    return false;
                }
            }
        }
    }
    
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
            var atts = document.createAttribute("id");
            atts.value = j + "-" + i;
            var name = document.createAttribute("name");
            name.value = "var" + atts.value;
            var style = document.createAttribute("style");
            style.value = "height: 20px; width: 35px;";
            newTextfield.setAttributeNode(atts);
            newTextfield.setAttributeNode(name);
            newTextfield.setAttributeNode(style);
            mycurrent_cell.appendChild(newTextfield);
            mycurrent_row.appendChild(mycurrent_cell);
            if ( i < col - 2 ) {
                var label = document.createElement("label");
                label.innerHTML = "x<sub>" + (i+1) + "</sub> +";
                mycurrent_row.appendChild(label);
            }
            else if ( i == col - 2 ) {
                var label = document.createElement("label");
                label.innerHTML = "x<sub>" + (i+1) + "</sub> =";
                mycurrent_row.appendChild(label);
            }
        }
        mytablebody.appendChild(mycurrent_row);
    }
    myTable.appendChild(mytablebody);
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
