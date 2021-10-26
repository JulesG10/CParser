# CParser


```html
 <id>, ?...<id> {
    ?...<attribute>: ...<attribute_value>;
}

<attribute_value> 
    ?{<inner_context>} 
    ?<func>(<func_param>)
    ?<number><type>(px,percent,rem)
    ?"<string>" 
```

```scss
.id_1, .id_2, .id_3
{
    background-color: url("http://color.rgb"), first, "[a-zA-Z0-9]+";
    align: center, x, y;
    click: open("/hello"), background, hidden, "<empty>";
    size: 100px, 100%;
}

.next_id {}
```