Naming things is hard. This sheet attempts to make it easier.
Although these suggestions can be applied to any programming language, I will use JavaScript to illustrate them in practice.

## English language
* Use English language when naming your variables and functions.

## Naming convention
* Pick one naming convention and follow it. It may be camelCase, PascalCase, snake_case, or anything else, as long as it remains consistent. Many programming languages have their own traditions regarding naming conventions; check the documentation for your language or study some popular repositories on Github!

## S-I-D
* **Short**. A name must not take long to type and, therefore, remember;
* **Intuitive**. A name must read naturally, as close to the common speech as possible;
* **Descriptive**. A name must reflect what it does/possesses in the most efficient way.

## Avoid contractions
* Do **not** use contractions. They contribute to nothing but decreased readability of the code. Finding a short, descriptive name may be hard, but contraction is not an excuse for not doing so.
```js
class MenuItem {
  /* Method name duplicates the context (which is "MenuItem") */
  handleMenuItemClick = (event) => { ... }
  /* Reads nicely as `MenuItem.handleClick()` */
  handleClick = (event) => { ... }
}
```

## Reflect the expected result
* A name should reflect the expected result.
```javascript
/* Bad */
const isEnabled = itemCount > 3
return <Button disabled={!isEnabled} />

/* Good */
const isDisabled = itemCount <= 3
return <Button disabled={isDisabled} />
```

## Naming functions
* A/HC/LC pattern
* There is a useful pattern to follow when naming functions
  > prefix? + action (A) + high context (HC) + low context? (LC)
* Take a look at how this pattern may be applied in the table below.
![](https://img2022.cnblogs.com/blog/1347181/202202/1347181-20220217113536474-1584212810.png)
* Actions
  * get,set,reset,fetch,remove,delete,compose,handle
* Context
  * A domain that a function operates on.
* Prefixes
  * Prefix enhances the meaning of a variable. It is rarely used in function names.
  * is,has,should,min/max,prev/next

## Singular and Plurals
* Like a prefix, variable names can be made singular or plural depending on whether they hold a single value or multiple values.


原地址
[naming-cheatsheet](https://github.com/kettanaito/naming-cheatsheet)
